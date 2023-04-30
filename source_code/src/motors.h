#ifndef __MOTORS_H
#define __MOTORS_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>


#include "config.h"
#include "utils.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

void set_motors_speed(float velI, float velD);

#endif