/*
 * spi.c
 * 
 * Changed A little bit an original library
 * Grisha Gevorkyan
 * 
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1

#endif
//!-----------------SPI PART----------------------------------------------------//
void init_spi_master(void)
{       /* out: MOSI, SCK, /SS, in: MISO */
        DDRB = _BV(PB4) | _BV(PB5) | _BV(PB7);
        SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPI2X); /* F_SCK = F_CPU/2 */
}

void tx(uint8_t b)
{
        SPDR = b;
        while(!(SPSR & _BV(SPIF)));
}

void init_spi_slave(void)
{       /* out: MISO, in: MOSI, SCK, /SS */
        DDRB = _BV(PB6); SPCR = _BV(SPE); /* Enable SPI */
}

uint8_t rx(void)
{
        while(!(SPSR & _BV(SPIF)));
        return SPDR;
}

