#include "leds.h"

static uint32_t last_menu_blink_ms = 0;

static uint32_t last_sensor_led_wainting_ms = 0;
static const uint8_t NUM_SENSOR_LED_WAITING_STATES = 6;
static uint8_t sensor_led_wainting_state = 0;

static uint32_t last_sensor_strat_menu_ms = 0;
static uint8_t sensor_strat_menu_count = 0;
static int8_t sensor_strat_menu_increment = 1;

void set_menu_led_blink(uint32_t ms) {
  if (get_clock_ticks() - last_menu_blink_ms >= ms) {
    gpio_toggle(GPIOA, GPIO8);
    last_menu_blink_ms = get_clock_ticks();
  }
}

void set_menu_led(bool status) {
  if (status) {
    gpio_set(GPIOA, GPIO8);
  } else {
    gpio_clear(GPIOA, GPIO8);
  }
}

void set_sensor_led(bool status) {
  if (status) {
    gpio_set(GPIOC, GPIO15 | GPIO14 | GPIO13);
    gpio_set(GPIOB, GPIO10 | GPIO2 | GPIO1);
  } else {
    gpio_clear(GPIOC, GPIO15 | GPIO14 | GPIO13);
    gpio_clear(GPIOB, GPIO10 | GPIO2 | GPIO1);
  }
}

void set_sensor_led_waiting(uint32_t ms) {
  if (get_clock_ticks() - last_sensor_led_wainting_ms >= ms) {
    switch (sensor_led_wainting_state) {
      case 0:
        gpio_set(GPIOC, GPIO15);
        gpio_set(GPIOB, GPIO1);
        gpio_clear(GPIOB, GPIO2);
        gpio_clear(GPIOC, GPIO14);
        gpio_clear(GPIOB, GPIO10);
        gpio_clear(GPIOC, GPIO13);
        break;
      case 1:
        gpio_set(GPIOC, GPIO15);
        gpio_set(GPIOB, GPIO1);
        gpio_set(GPIOB, GPIO2);
        gpio_set(GPIOC, GPIO14);
        gpio_clear(GPIOB, GPIO10);
        gpio_clear(GPIOC, GPIO13);
        break;
      case 2:
        gpio_set(GPIOC, GPIO15);
        gpio_set(GPIOB, GPIO1);
        gpio_set(GPIOB, GPIO2);
        gpio_set(GPIOC, GPIO14);
        gpio_set(GPIOB, GPIO10);
        gpio_set(GPIOC, GPIO13);
        break;
      case 3:
        gpio_clear(GPIOC, GPIO15);
        gpio_clear(GPIOB, GPIO1);
        gpio_set(GPIOB, GPIO2);
        gpio_set(GPIOC, GPIO14);
        gpio_set(GPIOB, GPIO10);
        gpio_set(GPIOC, GPIO13);
        break;
      case 4:
        gpio_clear(GPIOC, GPIO15);
        gpio_clear(GPIOB, GPIO1);
        gpio_clear(GPIOB, GPIO2);
        gpio_clear(GPIOC, GPIO14);
        gpio_set(GPIOB, GPIO10);
        gpio_set(GPIOC, GPIO13);
        break;
      case 5:
        gpio_clear(GPIOC, GPIO15);
        gpio_clear(GPIOB, GPIO1);
        gpio_clear(GPIOB, GPIO2);
        gpio_clear(GPIOC, GPIO14);
        gpio_clear(GPIOB, GPIO10);
        gpio_clear(GPIOC, GPIO13);
        break;
    }
    sensor_led_wainting_state = (sensor_led_wainting_state + 1) % NUM_SENSOR_LED_WAITING_STATES;
    last_sensor_led_wainting_ms = get_clock_ticks();
  }
}

void set_sensor_led_starting(uint32_t ms_start) {
  switch ((uint8_t)ceil((ms_start + get_start_millis() - get_clock_ticks()) / 1000.0)) {
    case 0:
      gpio_clear(GPIOC, GPIO15);
      gpio_clear(GPIOB, GPIO1);
      gpio_clear(GPIOB, GPIO2);
      gpio_clear(GPIOC, GPIO14);
      gpio_clear(GPIOB, GPIO10);
      gpio_clear(GPIOC, GPIO13);
      break;
    case 1:
      gpio_set(GPIOC, GPIO15);
      gpio_set(GPIOB, GPIO1);
      gpio_clear(GPIOB, GPIO2);
      gpio_clear(GPIOC, GPIO14);
      gpio_clear(GPIOB, GPIO10);
      gpio_clear(GPIOC, GPIO13);
      break;
    case 2:
      gpio_set(GPIOC, GPIO15);
      gpio_set(GPIOB, GPIO1);
      gpio_set(GPIOB, GPIO2);
      gpio_set(GPIOC, GPIO14);
      gpio_clear(GPIOB, GPIO10);
      gpio_clear(GPIOC, GPIO13);
      break;
    default:
      gpio_set(GPIOC, GPIO15);
      gpio_set(GPIOB, GPIO1);
      gpio_set(GPIOB, GPIO2);
      gpio_set(GPIOC, GPIO14);
      gpio_set(GPIOB, GPIO10);
      gpio_set(GPIOC, GPIO13);
      break;
  }
}

void set_sensor_led_debug(enum LEDS index, bool state) {
  switch (index) {
    case LED_SENSOR_FRONT_RIGHT:
      if (state) {
        gpio_set(GPIOC, GPIO15);
      } else {
        gpio_clear(GPIOC, GPIO15);
      }
      break;
    case LED_SENSOR_FRONT_LEFT:
      if (state) {
        gpio_set(GPIOB, GPIO1);
      } else {
        gpio_clear(GPIOB, GPIO1);
      }
      break;
    case LED_SENSOR_ANGLE_LEFT:
      if (state) {
        gpio_set(GPIOB, GPIO2);
      } else {
        gpio_clear(GPIOB, GPIO2);
      }
      break;
    case LED_SENSOR_ANGLE_RIGHT:
      if (state) {
        gpio_set(GPIOC, GPIO14);
      } else {
        gpio_clear(GPIOC, GPIO14);
      }
      break;
    case LED_SENSOR_LEFT:
      if (state) {
        gpio_set(GPIOB, GPIO10);
      } else {
        gpio_clear(GPIOB, GPIO10);
      }
      break;
    case LED_SENSOR_RIGHT:
      if (state) {
        gpio_set(GPIOC, GPIO13);
      } else {
        gpio_clear(GPIOC, GPIO13);
      }
      break;
    case LED_SENSOR_LINE_LEFT:
      if (state) {
        gpio_set(GPIOB, GPIO10 | GPIO2 | GPIO1);
      }
      break;
    case LED_SENSOR_LINE_RIGHT:
      if (state) {
        gpio_set(GPIOC, GPIO15 | GPIO14 | GPIO13);
      }
      break;
  }
}

void set_sensor_led_menu_opening(enum OPENINGS opening) {
  switch (opening) {
    case OPENING_FRONT:
      gpio_clear(GPIOC, GPIO14 | GPIO13);
      gpio_clear(GPIOB, GPIO10 | GPIO2);
      gpio_set(GPIOC, GPIO15);
      gpio_set(GPIOB, GPIO1);
      break;
    case OPENING_RIGHT:
      gpio_clear(GPIOC, GPIO15);
      gpio_clear(GPIOB, GPIO10 | GPIO2 | GPIO1);
      gpio_set(GPIOC, GPIO13 | GPIO14);
      break;
    case OPENING_RIGHT_ARC:
      gpio_clear(GPIOC, GPIO14);
      gpio_clear(GPIOB, GPIO10 | GPIO2 | GPIO1);
      gpio_set(GPIOC, GPIO13 | GPIO15);
      break;
    case OPENING_LEFT:
      gpio_clear(GPIOC, GPIO15 | GPIO14 | GPIO13);
      gpio_clear(GPIOB, GPIO1);
      gpio_set(GPIOB, GPIO2 | GPIO10);
      break;
    case OPENING_LEFT_ARC:
      gpio_clear(GPIOC, GPIO15 | GPIO14 | GPIO13);
      gpio_clear(GPIOB, GPIO2);
      gpio_set(GPIOB, GPIO1 | GPIO10);
      break;
    case OPENING_BACK:
      gpio_clear(GPIOC, GPIO15 | GPIO14);
      gpio_clear(GPIOB, GPIO2 | GPIO1);
      gpio_set(GPIOB, GPIO10);
      gpio_set(GPIOC, GPIO13);
      break;
  }
}

void set_sensor_led_menu_strat(enum STRATS strat) {
  switch (strat) {
    case STRAT_KEEPING_INSIDE:

      gpio_clear(GPIOC, GPIO15 | GPIO14);
      gpio_clear(GPIOB, GPIO2 | GPIO1);
      if (get_clock_ticks() - last_sensor_strat_menu_ms > 150) {
        gpio_toggle(GPIOB, GPIO10);
        gpio_toggle(GPIOC, GPIO13);
        last_sensor_strat_menu_ms = get_clock_ticks();
      }
      break;
    case STRAT_PID:
      if (get_clock_ticks() - last_sensor_strat_menu_ms > 50) {
        gpio_clear(GPIOC, GPIO15 | GPIO14 | GPIO13);
        gpio_clear(GPIOB, GPIO10 | GPIO2 | GPIO1);
        switch (sensor_strat_menu_count) {
          case 0:
            gpio_set(GPIOB, GPIO10);
            break;
          case 1:
            gpio_set(GPIOB, GPIO2);
            break;
          case 2:
            gpio_set(GPIOB, GPIO1);
            break;
          case 3:
            gpio_set(GPIOC, GPIO15);
            break;
          case 4:
            gpio_set(GPIOC, GPIO14);
            break;
          case 5:
            gpio_set(GPIOC, GPIO13);
            break;

          default:
            break;
        }

        if (sensor_strat_menu_count == 0 && sensor_strat_menu_increment < 0) {
          sensor_strat_menu_increment = 1;
        } else if (sensor_strat_menu_count == NUM_SENSORS - NUM_SENSORS_LINE - 1 && sensor_strat_menu_increment > 0) {
          sensor_strat_menu_increment = -1;
        }
        sensor_strat_menu_count += sensor_strat_menu_increment;
        last_sensor_strat_menu_ms = get_clock_ticks();
      }
      break;
    case STRAT_STEPS:
      if (get_clock_ticks() - last_sensor_strat_menu_ms > 100) {
        gpio_clear(GPIOC, GPIO15 | GPIO14 | GPIO13);
        gpio_clear(GPIOB, GPIO10 | GPIO2 | GPIO1);
        switch (sensor_strat_menu_count) {
          case 0:
            gpio_set(GPIOB, GPIO10);
            break;
          case 1:
            gpio_set(GPIOB, GPIO2);
            break;
          case 2:
            gpio_set(GPIOB, GPIO1);
            break;
          case 3:
            gpio_set(GPIOC, GPIO15);
            break;
          case 4:
            gpio_set(GPIOC, GPIO14);
            break;
          case 5:
            gpio_set(GPIOC, GPIO13);
            break;

          default:
            break;
        }

        if (sensor_strat_menu_count == 0 && sensor_strat_menu_increment < 0) {
          sensor_strat_menu_increment = 1;
        } else if (sensor_strat_menu_count == NUM_SENSORS - NUM_SENSORS_LINE - 1 && sensor_strat_menu_increment > 0) {
          sensor_strat_menu_increment = -1;
        }
        sensor_strat_menu_count += sensor_strat_menu_increment;
        last_sensor_strat_menu_ms = get_clock_ticks();
      }
      break;
  }
}
