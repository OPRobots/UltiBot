#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"
#include "delay.h"
#include "math.h"
#include "stdio.h"
#include <libopencm3/stm32/gpio.h>

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);
void control_main_loop(void);

#endif