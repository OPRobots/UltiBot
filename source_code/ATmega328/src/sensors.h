#ifndef SENSOR_H
#define SENSOR_H

#include "commons.h"

enum SENSORS {
  SENSOR_RIGHT = 0,
  SENSOR_ANGLE_RIGHT = 1,
  SENSOR_FRONT_RIGHT = 2,
  SENSOR_FRONT_LEFT = 3,
  SENSOR_ANGLE_LEFT = 4,
  SENSOR_LEFT = 5,
  SENSOR_LINE_RIGHT = 6,
  SENSOR_LINE_LEFT = 7,
};

#define SENSOR_RIVAL_MIN 150
#define SENSOR_RIVAL_MAX 400

#define SENSOR_LINE_THRESHOLD 250

void update_sensors_readings(void);
int get_sensor_raw(enum SENSORS index);
int get_sensor_calibrated(enum SENSORS index);
bool get_sensor_digital(enum SENSORS index);
int get_sensor_position();

#endif