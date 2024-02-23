#include "menu.h"

static enum MENUS menu = MENU_NONE;
static uint32_t menu_btn_ms = 0;

static void menu_long_press(void) {
  set_sensor_led(false);
  menu = (menu + 1) % NUM_MENUS;
}

static void menu_short_press(void) {
  set_sensor_led(false);
  switch (menu) {
    case MENU_OPENING:
      set_opening((get_opening() + 1) % NUM_OPENINGS);
      break;
    case MENU_STRAT:
      set_strat((get_strat() + 1) % NUM_STRATS);
      break;
    case MENU_DEBUG:
      set_debug_from_menu((get_debug_from_menu() + 1) % NUM_DEBUGS);
      break;
    default:
      // Do nothing.
      break;
  }
}

static void show_menu_leds(void) {
  switch (menu) {
    case MENU_NONE:
      set_menu_led(false);
      set_sensor_led(false);
      break;
    case MENU_OPENING:
      set_menu_led_blink(350);
      set_sensor_led_menu_opening(get_opening());
      break;
    case MENU_STRAT:
      set_menu_led_blink(150);
      set_sensor_led_menu_strat(get_strat());
      break;
    case MENU_DEBUG:
      set_menu_led(true);
      break;
  }
}

static void menu_loop(void) {
  switch (menu) {
    case MENU_DEBUG:
      set_menu_led(true);
      debug_from_menu();
      break;
    default:
      show_menu_leds();
      break;
  }
}

void check_menu_button(void) {
  if (get_menu_mode_btn()) {
    menu_btn_ms = get_clock_ticks();
    while (get_menu_mode_btn()) {
      if (get_clock_ticks() - menu_btn_ms >= 250) {
        menu_long_press();
        while (get_menu_mode_btn()) {
          menu_loop();
        }
      }
      menu_loop();
    }
    if (get_clock_ticks() - menu_btn_ms < 250) {
      menu_short_press();
    }
  }
  menu_loop();
}

void menu_mode_change(void){
  menu_long_press();
}

void menu_config_change(void){
  menu_short_press();
}