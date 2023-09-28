#include "sensors.h"

static uint8_t sensors_adc[NUM_SENSORS] = {ADC_CHANNEL7, ADC_CHANNEL6, ADC_CHANNEL3, ADC_CHANNEL5, ADC_CHANNEL2, ADC_CHANNEL4, ADC_CHANNEL1, ADC_CHANNEL0};
static volatile uint16_t sensors_raw[NUM_SENSORS];

static bool sensors_digital[NUM_SENSORS - NUM_SENSORS_LINE];
static uint16_t sensors_weight[NUM_SENSORS - NUM_SENSORS_LINE];
static int16_t sensors_position = 0;

uint8_t get_sensors_num() {
  return NUM_SENSORS;
}

uint8_t *get_sensors() {
  return sensors_adc;
}

volatile uint16_t *get_sensors_raw() {
  return sensors_raw;
}

uint16_t get_sensor_raw(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    return LECTURA_MAXIMO_SENSORES_LINEA - sensors_raw[index];
  } else {
    return sensors_raw[index];
  }
}

uint16_t get_sensor_calibrated(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    if (sensors_raw[index] > LINE_SENSOR_THRESHOLD) {
      return LECTURA_MAXIMO_SENSORES_LINEA;
    } else {
      return LECTURA_MINIMO_SENSORES_LINEA;
    }
  } else {
    if (sensors_raw[index] > RIVAL_SENSOR_THRESHOLD && sensors_raw[index] < RIVAL_SENSOR_MAX) {
      return sensors_raw[index];
    } else {
      return 0;
    }
  }
}

bool get_sensor_digital(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    if (sensors_raw[index] > LINE_SENSOR_THRESHOLD) {
      return true;
    }
  } else {
    if (sensors_raw[index] > RIVAL_SENSOR_THRESHOLD && sensors_raw[index] < RIVAL_SENSOR_MAX) {
      return true;
    }
  }
  return false;
}

void update_sensors_readings(void) {
  uint32_t sensor_avg = 0;
  uint32_t sensor_sum = 0;
  for (uint8_t sensor = 0; sensor < NUM_SENSORS - NUM_SENSORS_LINE; sensor++) {
    sensors_digital[sensor] = get_sensor_digital(sensor + 1); // sensors_raw[sensor] > RIVAL_SENSOR_THRESHOLD;
    sensors_weight[sensor] = sensors_digital[sensor] ? map(sensors_raw[sensor + 1], RIVAL_SENSOR_THRESHOLD, RIVAL_SENSOR_MAX, 1, 1000) : 0;

    // printf("%d - %d | ", sensors_digital[sensor], sensors_weight[sensor]);

    if (sensors_digital[sensor]) {
      sensor_avg += sensors_weight[sensor] * (sensor + 1) * 1000;
      sensor_sum += sensors_weight[sensor];
    }
  }
  // printf(" > %ld - %ld |", sensor_avg, sensor_sum);
  sensors_position = sensor_avg / sensor_sum - ((1000 * (NUM_SENSORS - NUM_SENSORS_LINE + 1)) / 2);
  // printf("%d ", -3500);
  // printf("%d ", 3500);
  // printf("%d\n", sensors_position);
}

int16_t get_sensors_position(void) {
  return sensors_position;
}