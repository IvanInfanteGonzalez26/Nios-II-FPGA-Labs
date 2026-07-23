#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

int main()
{
    unsigned char sclk = 0;
    unsigned char dout = 0;
    unsigned char din = 0;
    unsigned char cs = 0;
    unsigned char sw = 0;
    unsigned char canal = 0;
    unsigned char comando = 0;

    unsigned int valor_adc = 0;
    unsigned int valor_leds = 0;

    volatile int count = 0;
    int i = 0;

    // Inicializacion
    sclk = 0;
    cs = 0;
    din = 0;

    IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_SCLK_BASE, sclk);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_CS_BASE, cs);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_DIN_BASE, din);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_BASE, 0);

    while (1) {

        // Leer switch
        sw = IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCH_BASE) & 1;

        if (sw == 0) {
            canal = 0;
            comando = 0x22;
        } else {
            canal = 1;
            comando = 0x32;
        }

        // Seleccionar canal
        for (i = 0; i < 12; i++) {

            if (i < 6) {
                din = (comando >> (5 - i)) & 1;
            } else {
                din = 0;
            }

            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_DIN_BASE, din);

            sclk = 1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_SCLK_BASE, sclk);

            sclk = 0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_SCLK_BASE, sclk);
        }

        for (count = 0; count < 200; count++);

        // Iniciar conversion
        cs = 1;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_CS_BASE, cs);

        for (count = 0; count < 20; count++);

        cs = 0;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_CS_BASE, cs);

        for (count = 0; count < 1000; count++);

        // Leer ADC
        valor_adc = 0;

        for (i = 0; i < 12; i++) {

            if (i < 6) {
                din = (comando >> (5 - i)) & 1;
            } else {
                din = 0;
            }

            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_DIN_BASE, din);

            sclk = 1;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_SCLK_BASE, sclk);

            dout = IORD_ALTERA_AVALON_PIO_DATA(PIO_ADC_DOUT_BASE) & 1;
            valor_adc = (valor_adc << 1) | dout;

            sclk = 0;
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_ADC_SCLK_BASE, sclk);
        }

        // Mostrar en LEDs
        valor_leds = (valor_adc >> 2) & 0x3FF;
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_LEDS_BASE, valor_leds);

        // Mostrar en printf
        printf("Canal: %u    ADC: %u    LEDs: %u\n",
               canal, valor_adc, valor_leds);
    }

    return 0;
}
