#include "spi.h"

uint8_t spi_read_register(uint8_t address) {
  uint8_t reading;

  gpio_clear(GPIOB, GPIO12);
  spi_send(SPI2, address);
  spi_read(SPI2);
  spi_send(SPI2, 0x00);
  reading = spi_read(SPI2);
  gpio_set(GPIOB, GPIO12);

  return reading;
}

void spi_write_register(uint8_t address, uint8_t value) {
  gpio_clear(GPIOB, GPIO12);
  spi_send(SPI2, address);
  spi_read(SPI2);
  spi_send(SPI2, value);
  spi_read(SPI2);
  gpio_set(GPIOB, GPIO12);
  // delay(150);
}

