#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "config.h"
#include "delay.h"
#include "math.h"
#include "stdio.h"
#include <libopencm3/stm32/gpio.h>

bool get_start_btn(void);
bool get_menu_mode_btn(void);

#endif