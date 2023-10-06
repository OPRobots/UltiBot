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

#define NUM_OPENINGS 6
enum OPENINGS {
  OPENING_FRONT = 0,
  OPENING_RIGHT = 1,
  OPENING_RIGHT_ARC = 2,
  OPENING_LEFT = 3,
  OPENING_LEFT_ARC = 4,
  OPENING_BACK = 5,
};

#define NUM_STRATS 2
enum STRATS {
  STRAT_KEEPING_INSIDE = 0,
  STRAT_PID = 1,
};

#define BASE_SPEED 70
#define TURN_SPEED 80

#define STRAT_PID_KP 0.5
#define STRAT_PID_KD 50

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);

void set_opening(enum OPENINGS opening);
enum OPENINGS get_opening(void);
void set_strat(enum STRATS strat);
enum STRATS get_strat(void);

void control_main_loop(void);

#endif