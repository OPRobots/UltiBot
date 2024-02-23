#ifndef __EEPROM_H
#define __EEPROM_H

#include <libopencm3/stm32/flash.h>

#include <delay.h>
#include <leds.h>

#define EEPROM_SECTOR 5
#define EEPROM_BASE_ADDRESS (0x08020000)

#define DATA_LENGTH (RC5_DATA_LENGTH)

#define DATA_INDEX_RC5 0

void eeprom_save(void);
void eeprom_load(void);
void eeprom_clear(void);
void eeprom_set_data(uint16_t index, uint16_t *data, uint16_t length);
uint16_t *eeprom_get_data(void);

#endif
