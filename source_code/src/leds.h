#ifndef __LEDS_H
#define __LEDS_H

#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#include <math.h>
#include <stdio.h>

void clear_rgb(void);
void calc_rgb_timings(void);
void show_rgb(void);
void manage_rgb(void);
void set_rgb(uint8_t index, int r, int g, int b);

#endif