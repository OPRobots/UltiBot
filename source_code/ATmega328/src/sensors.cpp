#include "sensors.h"

int sensors_raw[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensors_calibrated[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensors_position = 0;

/**
 * @brief Actualiza los valores de los sensores y calcula sus valores calibrados
 * 
 */
void update_sensors_readings() {
  sensors_raw[0] = analogRead(SENSOR_LAT_DER);
  sensors_raw[1] = analogRead(SENSOR_ANG_DER);
  sensors_raw[2] = analogRead(SENSOR_FRO_DER);
  sensors_raw[3] = analogRead(SENSOR_FRO_IZQ);
  sensors_raw[4] = analogRead(SENSOR_ANG_IZQ);
  sensors_raw[5] = analogRead(SENSOR_LAT_IZQ);

  for (int sensor = 0; sensor < 6; sensor++) {
    if (!(sensors_raw[sensor] >= SENSOR_RIVAL_MIN /*  && sensors_raw[sensor] <= SENSOR_RIVAL_MAX */)) {
      sensors_calibrated[sensor] = 0;
    } else {
      //TODO: revisar el 100 del mapeo de sensores
      //TODO: revisar el signo del mapeo (0-100 o 100-0??)
      sensors_calibrated[sensor] = constrain(map(sensors_raw[sensor], SENSOR_RIVAL_MIN, SENSOR_RIVAL_MAX, 0, 100), 0, 100);
    }
  }

  sensors_raw[6] = analogRead(SENSOR_LIN_DER);
  sensors_raw[7] = analogRead(SENSOR_LIN_IZQ);

  sensors_calibrated[6] = sensors_raw[6] <= SENSOR_LINE_THRESHOLD ? 1 : 0;
  sensors_calibrated[7] = sensors_raw[7] <= SENSOR_LINE_THRESHOLD ? 1 : 0;

  int sensor_avg = 0;
  int sensor_sum = 0;
  int count = 0;
  for (int sensor = 0; sensor < 6; sensor++) {
    if (get_sensor_digital((enum SENSORS)sensor)) {
      sensor_avg += (sensors_calibrated[sensor] > 0 ? 1 : 0) * (sensor + 1) * 1000;
      sensor_sum += (sensors_calibrated[sensor] > 0 ? 1 : 0);
      count++;
    }
  }
  if (count > 0) {
    sensors_position = map(sensor_avg / sensor_sum - (7 * 1000 / 2), -3500, 3500, -100, 100);
  } else {
    // sensors_position = 0;
  }
}

int get_sensor_raw(enum SENSORS index) {
  return sensors_raw[index];
}

int get_sensor_calibrated(enum SENSORS index) {
  return sensors_calibrated[index];
}

bool get_sensor_digital(enum SENSORS index) {
  return sensors_calibrated[index] >= 1 ? true : false;
}

int get_sensor_position() {
  return sensors_position;
}