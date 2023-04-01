#ifndef __SENSORS_H
#define __SENSORS_H

#include "config.h"
#include "delay.h"
#include "leds.h"
#include "stdint.h"
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define NUM_SENSORS 8
#define NUM_SENSORS_LINE 2

uint8_t *get_sensors(void);
uint8_t get_sensors_num(void);
volatile uint16_t *get_sensors_raw(void);

#endif