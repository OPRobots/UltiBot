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

void debug_sensors_leds(void);
void debug_sensors_raw(void);
void debug_sensors_calibrated(void);
void debug_sensors_position(void);

#endif