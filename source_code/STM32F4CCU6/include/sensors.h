#ifndef __SENSORS_H
#define __SENSORS_H

#include "config.h"
#include "delay.h"
#include "leds.h"
#include "stdint.h"
#include "utils.h"
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define NUM_SENSORS 8
#define NUM_SENSORS_LINE 2
#define RIVAL_SENSOR_THRESHOLD 350
#define RIVAL_SENSOR_MAX 2600
#define LINE_SENSOR_THRESHOLD 2500

enum SENSORS {
  SENSOR_LINE_LEFT = 0,
  SENSOR_LEFT = 1,
  SENSOR_ANGLE_LEFT = 2,
  SENSOR_FRONT_LEFT = 3,
  SENSOR_FRONT_RIGHT = 4,
  SENSOR_ANGLE_RIGHT = 5,
  SENSOR_RIGHT = 6,
  SENSOR_LINE_RIGHT = 7
};

uint8_t *get_sensors(void);
uint8_t get_sensors_num(void);
volatile uint16_t *get_sensors_raw(void);
uint16_t get_sensor_raw(enum SENSORS index);
uint16_t get_sensor_calibrated(enum SENSORS index);
bool get_sensor_digital(enum SENSORS index);

void update_sensors_readings(void);
int16_t get_sensors_position(void);

#endif