#include "debug.h"

void debug_sensors(void) {
  for (uint8_t i = 0; i < NUM_SENSORS - NUM_SENSORS_LINE; i++) {
    uint16_t value = get_sensor_calibrated(i);

    if (value > 0) {
      // uint8_t r = 0;
      // uint8_t g = 0;
      // uint8_t b = 0;

      // uint8_t percent = map(value, RIVAL_SENSOR_THRESHOLD, RIVAL_SENSOR_MAX, 0, 100);

      // r = percent >= 25 ? map(percent, 25, 100, 0, 50) : 0;
      // g = percent <= 75 ? map(percent, 75, 0, 0, 50) : 0;

      switch (i) {
        case SENSOR_FRONT_RIGHT:
        //TODO: mostrar estado en leds
          break;
        case SENSOR_FRONT_LEFT:
        //TODO: mostrar estado en leds
          break;
        case SENSOR_ANGLE_LEFT:
        //TODO: mostrar estado en leds
          break;
        case SENSOR_ANGLE_RIGHT:
        //TODO: mostrar estado en leds
          break;
        case SENSOR_LEFT:
        //TODO: mostrar estado en leds
          break;
        case SENSOR_RIGHT:
        //TODO: mostrar estado en leds
          break;
      }
    }
  }
  if (get_sensor_calibrated(SENSOR_LINE_LEFT) < LINE_SENSOR_THRESHOLD || get_sensor_calibrated(SENSOR_LINE_RIGHT) < LINE_SENSOR_THRESHOLD) {
    //TODO: mostrar estado en leds
  }
}