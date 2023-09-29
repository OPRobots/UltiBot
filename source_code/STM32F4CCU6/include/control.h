#ifndef __CONTROL_H
#define __CONTROL_H

#include <libopencm3/stm32/gpio.h>

#include <stdio.h>

#include "config.h"
#include "debug.h"
#include "delay.h"
#include "math.h"
#include "motors.h"

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
  STRAT_PID,
};

#define BASE_SPEED 70
#define TURN_SPEED 80

#define STRAT_PID_KP 0.5
#define STRAT_PID_KD 50

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);

void set_opening(enum OPENINGS opening);
void set_strat(enum STRATS strat);

void control_main_loop(void);

#endif