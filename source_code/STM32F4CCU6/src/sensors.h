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
#define RIVAL_SENSOR_THRESHOLD 550
#define RIVAL_SENSOR_MAX 2600
#define LINE_SENSOR_THRESHOLD 2000

enum SENSORS { SENSOR_FRONT_RIGHT = 0,
               SENSOR_FRONT_LEFT = 1,
               SENSOR_ANGLE_LEFT = 2,
               SENSOR_ANGLE_RIGHT = 3,
               SENSOR_LEFT = 5,
               SENSOR_RIGHT = 4,
               SENSOR_LINE_LEFT = 6,
               SENSOR_LINE_RIGHT = 7 };

uint8_t *get_sensors(void);
uint8_t get_sensors_num(void);
volatile uint16_t *get_sensors_raw(void);
uint16_t get_sensor_raw(enum SENSORS index);
uint16_t get_sensor_calibrated(enum SENSORS index);
bool get_sensor_digital(enum SENSORS index);

#endif