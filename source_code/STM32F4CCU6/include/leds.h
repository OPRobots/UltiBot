#ifndef __LEDS_H
#define __LEDS_H

#include "config.h"
#include "delay.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <math.h>
#include <stdio.h>

enum LEDS { LED_SENSOR_FRONT_RIGHT = 5,
            LED_SENSOR_FRONT_LEFT = 2,
            LED_SENSOR_ANGLE_LEFT = 4,
            LED_SENSOR_ANGLE_RIGHT = 3,
            LED_SENSOR_LEFT = 1,
            LED_SENSOR_RIGHT = 6,
            LED_SENSOR_LINE_LEFT = 0,
            LED_SENSOR_LINE_RIGHT = 7 };

void set_sensor_led(enum LEDS index, bool state);

#endif