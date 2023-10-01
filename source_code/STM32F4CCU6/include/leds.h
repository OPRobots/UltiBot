#ifndef __LEDS_H
#define __LEDS_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <math.h>
#include <stdio.h>

#include "config.h"
#include "control.h"
#include "delay.h"

enum LEDS { LED_SENSOR_FRONT_RIGHT = 5,
            LED_SENSOR_FRONT_LEFT = 2,
            LED_SENSOR_ANGLE_LEFT = 4,
            LED_SENSOR_ANGLE_RIGHT = 3,
            LED_SENSOR_LEFT = 1,
            LED_SENSOR_RIGHT = 6,
            LED_SENSOR_LINE_LEFT = 0,
            LED_SENSOR_LINE_RIGHT = 7 };

void set_menu_led_blink(uint32_t ms);
void set_menu_led(bool status);
void set_sensor_led(bool status);
void set_sensor_led_waiting(uint32_t ms);
void set_sensor_led_starting(uint32_t ms_start);
void set_sensor_led_debug(enum LEDS index, bool state);
void set_sensor_led_menu_opening(enum OPENINGS opening);
void set_sensor_led_menu_strat(enum STRATS strat);

#endif