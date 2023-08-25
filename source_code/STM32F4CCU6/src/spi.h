#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>

#include "setup.h"

uint8_t spi_read_register(uint8_t addr);
void spi_write_register(uint8_t addr, uint8_t value);

#endif