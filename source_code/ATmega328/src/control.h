#ifndef CONTROL_H
#define CONTROL_H

#include "commons.h"
#include "sensors.h"
#include "motors.h"
#include "leds.h"

enum STATUS {
  STATE_KEEPING_INSIDE,
  STATE_OPENING,
  STATE_RUNNING,
};

#define OPENING_COUNT 4
enum OPENINGS {
  OPENING_FRONT = 0,
  OPENING_RIGHT = 1,
  OPENING_LEFT = 2,
  OPENING_BACK = 3,
};

#define STRAT_COUNT 3
enum STRATS {
  STRAT_KEEPING_INSIDE = 0,
  STRAT_SEARCH_FOLLOW = 1,
  STRAT_CHIQUITO_STEPS = 2,
};

bool is_competicion_iniciada(void);
void set_competicion_iniciada(bool state);

void set_opening(enum OPENINGS opening);
void set_strat(enum STRATS strat);

void control_main_loop(void);

#endif