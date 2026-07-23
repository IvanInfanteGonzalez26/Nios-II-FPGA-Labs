#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "imagen_rgb332.h"

#define IMAGE_WIDTH   160
#define IMAGE_HEIGHT  120
#define PIXEL_COUNT   (IMAGE_WIDTH * IMAGE_HEIGHT)

static void write_pixel(unsigned int address, unsigned char color)
{
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_MEM_WRITE_BASE, 0);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_MEM_ADDRESS_BASE, address);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_MEM_DATA_BASE, color);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_MEM_WRITE_BASE, 1);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_MEM_WRITE_BASE, 0);
}

int main(void)
{
    unsigned int address;

    printf("Cargando imagen RGB332 de 160x120...\n");

    for (address = 0; address < PIXEL_COUNT; ++address) {
        write_pixel(address, imagen_rgb332[address]);
    }

    printf("Imagen terminada: %u pixeles escritos.\n", PIXEL_COUNT);

    while (1) {
        /* La RAM conserva la imagen y el controlador VGA la muestra. */
    }

    return 0;
}
