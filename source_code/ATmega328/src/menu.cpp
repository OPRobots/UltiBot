#include "menu.h"

int modoConfig = 0;
#define MODE_NOTHING 0
#define MODE_OPENING 1
#define MODE_STRAT 2
#define MODE_DEBUG 3

int valoresConfig[4] = {0, 0, 0, 0};
int numValoresConfig[4] = {0, OPENING_COUNT - 1, STRAT_COUNT - 1, 0};

static void handle_menu_mode() {
  if (get_menu_mode_btn()) {
    modoConfig++;
    if (modoConfig > MODE_STRAT) {
      modoConfig = MODE_NOTHING;
    }
    while (get_menu_mode_btn()) {
    }
  }

  switch (modoConfig) {
    case MODE_NOTHING:
      set_led_status(false);
      break;
    case MODE_OPENING:
      set_led_status_warning(50);
      break;
    case MODE_STRAT:
      set_led_status_warning(200);
      break;
    case MODE_DEBUG:
      set_led_status(true);
      break;
  }
}

static void handle_menu_value() {
  if (get_menu_up_btn()) {
    valoresConfig[modoConfig]++;
    valoresConfig[modoConfig] = constrain(valoresConfig[modoConfig], 0, numValoresConfig[modoConfig]);
    while (get_menu_up_btn()) {
    }
  } else if (get_menu_down_btn()) {
    valoresConfig[modoConfig]--;
    valoresConfig[modoConfig] = constrain(valoresConfig[modoConfig], 0, numValoresConfig[modoConfig]);
    while (get_menu_down_btn()) {
    }
  }
  switch (modoConfig) {
    case MODE_NOTHING:
      set_leds(false);
      break;
    case MODE_OPENING:
      set_opening((enum OPENINGS)valoresConfig[modoConfig]);
      switch (valoresConfig[modoConfig]) {
        case OPENING_FRONT:
          set_leds(false);
          set_led_center(true);
          break;
        case OPENING_RIGHT:
          set_leds(false);
          set_led_right(true);
          break;
        case OPENING_LEFT:
          set_leds(false);
          set_led_left(true);
          break;
        case OPENING_BACK:
          set_leds(false);
          set_led_right(true);
          set_led_left(true);
          break;
      }
      break;
    case MODE_STRAT:
      set_strat((enum STRATS)valoresConfig[modoConfig]);
      switch (valoresConfig[modoConfig]) {
        case STRAT_KEEPING_INSIDE:
          set_led_center(false);
          set_led_right_warning(75);
          set_led_left_warning(75);
          break;
        case STRAT_SEARCH_FOLLOW:
          set_led_center_warning(75);
          set_led_right(false);
          set_led_left(false);
          break;
        case STRAT_CHIQUITO_STEPS:
          set_led_center_warning(200);
          delay(25);
          set_led_right_warning(75);
          set_led_left_warning(75);
          break;
      }

      break;
  }
}

void handle_menu(void) {
  handle_menu_mode();
  handle_menu_value();
}

void reset_menu(void) {
  modoConfig = MODE_NOTHING;
  handle_menu_mode();
}