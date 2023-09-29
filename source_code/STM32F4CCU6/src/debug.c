#include "debug.h"

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
  for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
    printf("%*d - ", 4, get_sensor_raw(sensor));
  }
  printf("\n");
  delay(50);
}

void debug_sensors_calibrated(void) {
  for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
    printf("%*d - ", 4, get_sensor_calibrated(sensor));
  }
  printf("\n");
  delay(50);
}

void debug_sensors_position(void) {
  printf("%*d\n", 4, get_sensors_position());
  delay(50);
}