#include "debug.h"

static enum DEBUGS debug = DEBUG_SENSOR_LEDS;

static uint32_t debug_print_ms = 0;

void debug_sensors_leds(void) {
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    if (i == SENSOR_LINE_LEFT || i == SENSOR_LINE_RIGHT) {
      continue;
    }
    bool state = get_sensor_digital(i);

    switch (i) {
      case SENSOR_FRONT_RIGHT:
        set_sensor_led_debug(LED_SENSOR_FRONT_RIGHT, state);
        break;
      case SENSOR_FRONT_LEFT:
        set_sensor_led_debug(LED_SENSOR_FRONT_LEFT, state);
        break;
      case SENSOR_ANGLE_LEFT:
        set_sensor_led_debug(LED_SENSOR_ANGLE_LEFT, state);
        break;
      case SENSOR_ANGLE_RIGHT:
        set_sensor_led_debug(LED_SENSOR_ANGLE_RIGHT, state);
        break;
      case SENSOR_LEFT:
        set_sensor_led_debug(LED_SENSOR_LEFT, state);
        break;
      case SENSOR_RIGHT:
        set_sensor_led_debug(LED_SENSOR_RIGHT, state);
        break;
    }
  }

  // if (get_sensor_calibrated(SENSOR_LINE_LEFT) > LINE_SENSOR_THRESHOLD) {
  //   set_sensor_led_debug(LED_SENSOR_LINE_LEFT, true);
  // }
  // if (get_sensor_calibrated(SENSOR_LINE_RIGHT) > LINE_SENSOR_THRESHOLD) {
  //   set_sensor_led_debug(LED_SENSOR_LINE_RIGHT, true);
  // }
}

void debug_sensors_raw(void) {
  if (get_clock_ticks() - debug_print_ms > 50) {
    for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
      printf("%*d - ", 4, get_sensor_raw(sensor));
    }
    printf("\n");
    debug_print_ms = get_clock_ticks();
  }
}

void debug_sensors_calibrated(void) {
  if (get_clock_ticks() - debug_print_ms > 50) {
    for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
      printf("%*d - ", 4, get_sensor_calibrated(sensor));
    }
    printf("\n");
    debug_print_ms = get_clock_ticks();
  }
}

void debug_sensors_position(void) {

  if (get_clock_ticks() - debug_print_ms > 50) {
    printf("%*d\n", 4, get_sensors_position());
    debug_print_ms = get_clock_ticks();
  }
}

void set_debug_from_menu(enum DEBUGS _debug) {
  debug = _debug;
}

enum DEBUGS get_debug_from_menu(void) {
  return debug;
}

void debug_from_menu(void) {
  switch (debug) {
    case DEBUG_SENSOR_LEDS:
      debug_sensors_leds();
      break;
    case DEBUG_SENSOR_RAW:
      debug_sensors_raw();
      break;
    case DEBUG_SENSOR_CALIBRATED:
      debug_sensors_calibrated();
      break;
    case DEBUG_SENSOR_POSITION:
      debug_sensors_position();
      break;
  }
}