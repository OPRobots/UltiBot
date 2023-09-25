#include "debug.h"

void debug_sensors(void) {
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    if (i == SENSOR_LINE_LEFT || i == SENSOR_LINE_RIGHT) {
      continue;
    }
    uint16_t value = get_sensor_calibrated(i);

    switch (i) {
      case SENSOR_FRONT_RIGHT:
        set_sensor_led(LED_SENSOR_FRONT_RIGHT, value > RIVAL_SENSOR_THRESHOLD);
        break;
      case SENSOR_FRONT_LEFT:
        set_sensor_led(LED_SENSOR_FRONT_LEFT, value > RIVAL_SENSOR_THRESHOLD);
        break;
      case SENSOR_ANGLE_LEFT:
        set_sensor_led(LED_SENSOR_ANGLE_LEFT, value > RIVAL_SENSOR_THRESHOLD);
        break;
      case SENSOR_ANGLE_RIGHT:
        set_sensor_led(LED_SENSOR_ANGLE_RIGHT, value > RIVAL_SENSOR_THRESHOLD);
        break;
      case SENSOR_LEFT:
        set_sensor_led(LED_SENSOR_LEFT, value > RIVAL_SENSOR_THRESHOLD);
        break;
      case SENSOR_RIGHT:
        set_sensor_led(LED_SENSOR_RIGHT, value > RIVAL_SENSOR_THRESHOLD);
        break;
    }
  }

  if (get_sensor_calibrated(SENSOR_LINE_LEFT) > LINE_SENSOR_THRESHOLD) {
    set_sensor_led(LED_SENSOR_LINE_LEFT, true);
  }
  if (get_sensor_calibrated(SENSOR_LINE_RIGHT) > LINE_SENSOR_THRESHOLD) {
    set_sensor_led(LED_SENSOR_LINE_RIGHT, true);
  }
}