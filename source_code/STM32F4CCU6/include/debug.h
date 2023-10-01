#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>

#include "buttons.h"
#include "config.h"
#include "control.h"
#include "delay.h"
#include "motors.h"
#include "sensors.h"
#include "usart.h"

#define NUM_DEBUGS 4
enum DEBUGS {
  DEBUG_SENSOR_LEDS = 0,
  DEBUG_SENSOR_RAW = 1,
  DEBUG_SENSOR_CALIBRATED = 2,
  DEBUG_SENSOR_POSITION = 3
};

void debug_sensors_leds(void);
void debug_sensors_raw(void);
void debug_sensors_calibrated(void);
void debug_sensors_position(void);

void set_debug_from_menu(enum DEBUGS debug);
enum DEBUGS get_debug_from_menu(void);
void debug_from_menu(void);

#endif