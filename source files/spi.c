#include <LPC21xx.h>
#include "spi.h"
#include "spi_defines.h"

void Init_SPI0(void)
{
    PINSEL0 |= SCK0 | MISO0 | MOSI0;

    S0SPCCR = 60;
    S0SPCR  = MSTR | Mode_3;

    IODIR0 |= CS;
    IOSET0 |= CS;
}

u8 SPI0(u8 data)
{
    S0SPDR = data;
    while(!(S0SPSR & SPIF));
    return S0SPDR;
}
