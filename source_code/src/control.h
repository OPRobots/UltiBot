#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"
#include "delay.h"
#include "math.h"
#include "motors.h"
#include "stdio.h"
#include <libopencm3/stm32/gpio.h>

enum STRATS {
  STRAT_KEEPING_INSIDE = 0
};

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);

void set_strat(enum STRATS strat);
void control_main_loop(void);

#endif