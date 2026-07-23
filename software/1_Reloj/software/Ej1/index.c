#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_pio_regs.h"

#define BTN_RESET   0x01  // KEY(1) -> bit 0
#define BTN_INC_MIN 0x02  // KEY(2) -> bit 1
#define BTN_DEC_MIN 0x04  // KEY(3) -> bit 2

volatile unsigned int ms_global = 0;
volatile unsigned int ms_para_1s = 0;
volatile unsigned int segundos_pendientes = 0;

unsigned char seg7[10] = {
    0x40, // 0
    0x79, // 1
    0x24, // 2
    0x30, // 3
    0x19, // 4
    0x12, // 5
    0x02, // 6
    0x78, // 7
    0x00, // 8
    0x10  // 9
};

void timer_isr(void *context)
{
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);

    ms_global++;
    ms_para_1s++;

    if (ms_para_1s >= 1000)
    {
        ms_para_1s = 0;
        segundos_pendientes++;
    }
}

int main()
{
    int minutos = 0;
    int segundos = 0;

    int botones = 0;
    int botones_anterior = 0;
    int botones_nuevos = 0;

    int min_dec = 0;
    int min_uni = 0;
    int seg_dec = 0;
    int seg_uni = 0;

    unsigned int ahora = 0;
    unsigned int ultimo_reset = 0;
    unsigned int ultimo_inc = 0;
    unsigned int ultimo_dec = 0;

    unsigned int segundos_a_sumar = 0;
    alt_irq_context contexto;

    /*
     * Mostrar 00:00 al inicio
     */
    IOWR(PIO_1_HEX_BASE, 0, seg7[0]); // HEX0 segundos unidades
    IOWR(PIO_2_HEX_BASE, 0, seg7[0]); // HEX1 segundos decenas
    IOWR(PIO_3_HEX_BASE, 0, seg7[0]); // HEX2 minutos unidades
    IOWR(PIO_4_HEX_BASE, 0, seg7[0]); // HEX3 minutos decenas

    // Limpiar interrupción pendiente del timer
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);

    // Registrar ISR del timer
    alt_ic_isr_register(
        TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
        TIMER_0_IRQ,
        timer_isr,
        NULL,
        NULL
    );

    /*
     * Encender timer:
     * bit 0 = ITO   interrupción habilitada
     * bit 1 = CONT  modo continuo
     * bit 2 = START iniciar timer
     *
     * 0x07 = ITO + CONT + START
     */
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0x07);

    while (1)
    {
        /*
         * Leer botones de 3 bits.
         * En tu VHDL usaste not KEY:
         * no presionado = 0
         * presionado    = 1
         */
        botones = IORD(PIO_BOTONES_BASE, 0) & 0x07;

        // Detectar botón recién presionado
        botones_nuevos = botones & (~botones_anterior) & 0x07;

        ahora = ms_global;

        /*
         * KEY(1): Reset del reloj
         */
        if (botones_nuevos & BTN_RESET)
        //if ((botones_nuevos & BTN_RESET) && ((ahora - ultimo_reset) > 200))
        {
            minutos = 0;
            segundos = 0;

            contexto = alt_irq_disable_all();
            ms_para_1s = 0;
            segundos_pendientes = 0;
            alt_irq_enable_all(contexto);

            min_dec = minutos / 10;
            min_uni = minutos % 10;
            seg_dec = segundos / 10;
            seg_uni = segundos % 10;

            IOWR(PIO_1_HEX_BASE, 0, seg7[seg_uni]);
            IOWR(PIO_2_HEX_BASE, 0, seg7[seg_dec]);
            IOWR(PIO_3_HEX_BASE, 0, seg7[min_uni]);
            IOWR(PIO_4_HEX_BASE, 0, seg7[min_dec]);

            ultimo_reset = ahora;
        }

        /*
         * KEY(2): Aumentar minutos
         */
        if (botones_nuevos & BTN_INC_MIN)
        //if ((botones_nuevos & BTN_INC_MIN) && ((ahora - ultimo_inc) > 200))
        {
            minutos++;

            if (minutos > 99) minutos = 0;


            min_dec = minutos / 10;
            min_uni = minutos % 10;
            seg_dec = segundos / 10;
            seg_uni = segundos % 10;

            IOWR(PIO_1_HEX_BASE, 0, seg7[seg_uni]);
            IOWR(PIO_2_HEX_BASE, 0, seg7[seg_dec]);
            IOWR(PIO_3_HEX_BASE, 0, seg7[min_uni]);
            IOWR(PIO_4_HEX_BASE, 0, seg7[min_dec]);

            ultimo_inc = ahora;
        }

        /*
         * KEY(3): Disminuir minutos
         */
        if (botones_nuevos & BTN_DEC_MIN)
        //if ((botones_nuevos & BTN_DEC_MIN) && ((ahora - ultimo_dec) > 200))
        {
        	minutos--;
            if (minutos < 0) minutos = 0;


            min_dec = minutos / 10;
            min_uni = minutos % 10;
            seg_dec = segundos / 10;
            seg_uni = segundos % 10;

            IOWR(PIO_1_HEX_BASE, 0, seg7[seg_uni]);
            IOWR(PIO_2_HEX_BASE, 0, seg7[seg_dec]);
            IOWR(PIO_3_HEX_BASE, 0, seg7[min_uni]);
            IOWR(PIO_4_HEX_BASE, 0, seg7[min_dec]);

            ultimo_dec = ahora;
        }

        botones_anterior = botones;

        /*
         * Revisar si el timer ya acumuló segundos.
         */
        contexto = alt_irq_disable_all();
        segundos_a_sumar = segundos_pendientes;
        segundos_pendientes = 0;
        alt_irq_enable_all(contexto);

        while (segundos_a_sumar > 0)
        {
            segundos++;
            if (segundos >= 60)
            {
                segundos = 0;
                minutos++;

                if (minutos > 99) minutos = 0;

            }

            min_dec = minutos / 10;
            min_uni = minutos % 10;
            seg_dec = segundos / 10;
            seg_uni = segundos % 10;

            IOWR(PIO_1_HEX_BASE, 0, seg7[seg_uni]);
            IOWR(PIO_2_HEX_BASE, 0, seg7[seg_dec]);
            IOWR(PIO_3_HEX_BASE, 0, seg7[min_uni]);
            IOWR(PIO_4_HEX_BASE, 0, seg7[min_dec]);

            segundos_a_sumar--;
        }
    }

    return 0;
}
