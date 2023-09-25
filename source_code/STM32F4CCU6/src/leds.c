#include "leds.h"

void set_sensor_led(enum LEDS index, bool state) {
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
