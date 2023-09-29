#ifndef __MOTORS_H
#define __MOTORS_H

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#include "command.h"
#include "config.h"
#include "utils.h"


void set_motors_speed(int16_t velI, int16_t velD);

#endif