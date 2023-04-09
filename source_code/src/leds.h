#ifndef __LEDS_H
#define __LEDS_H

#include "config.h"
#include "delay.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <math.h>
#include <stdio.h>


enum LEDS { LED_FRONT = 3,
            LED_FRONT_LEFT = 4,
            LED_FRONT_RIGHT = 2,
            LED_BACK = 0,
            LED_BACK_LEFT = 5,
            LED_BACK_RIGHT = 1,
            LED_CENTER = 6 };

void init_rgb(void);
void set_rgb(enum LEDS led, int r, int g, int b);
void clear_rgb(void);
void update_rgb(void);
void manage_rgb(void);
void set_rainbow_rgb(enum LEDS led);
void set_loading_rgb(void);

#endif