#ifndef __LEDS_H
#define __LEDS_H

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <math.h>
#include <stdio.h>

void init_rgb(void);
void set_rgb(uint8_t index, int r, int g, int b);
void clear_rgb(void);
void update_rgb(void);
void manage_rgb(void);

#endif