#ifndef __MENU_H
#define __MENU_H

#include "leds.h"
#include "control.h"
#include "debug.h"

#define NUM_MENUS 4
enum MENUS {
  MENU_NONE = 0,
  MENU_OPENING = 1,
  MENU_STRAT = 2,
  MENU_DEBUG = 3
};

void check_menu_button(void);

#endif