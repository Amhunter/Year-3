/*
 * spi.h
 *
 * Grisha Gevorkyan
 * Changed a little bit original library
 *
 */
#ifndef SPI_H
#define SPI_H
#if 1
#endif

#include <stdint.h>

void init_spi_master(void);
void tx(uint8_t b);
void init_spi_slave(void);
uint8_t rx(void);

#endif
