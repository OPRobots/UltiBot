#ifndef __CONTROL_H
#define __CONTROL_H

#include "config.h"
#include "delay.h"
#include "math.h"
#include "motors.h"
#include "stdio.h"
#include <libopencm3/stm32/gpio.h>

enum STATUS {
  STATE_KEEPING_INSIDE,
  STATE_OPENING,
  STATE_RUNNING,
};
enum OPENINGS {
  OPENING_FRONT,
  OPENING_RIGHT,
  OPENING_LEFT,
  OPENING_BACK,
};
enum STRATS {
  STRAT_KEEPING_INSIDE,
};

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);

void set_opening(enum OPENINGS opening);
void set_strat(enum STRATS strat);

void control_main_loop(void);

#endif