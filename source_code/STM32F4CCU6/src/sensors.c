#include "sensors.h"

static uint8_t sensors_adc[NUM_SENSORS] = {ADC_CHANNEL7, ADC_CHANNEL6, ADC_CHANNEL3, ADC_CHANNEL5, ADC_CHANNEL2, ADC_CHANNEL4, ADC_CHANNEL1, ADC_CHANNEL0};
static volatile uint16_t sensors_raw[NUM_SENSORS];
// static volatile uint16_t sensors_last_raw[NUM_SENSORS];
static volatile uint16_t sensors_filtered[NUM_SENSORS];

static uint16_t sensors_filter_index = 0;
static uint16_t sensors_filter[NUM_SENSORS][SENSORS_FILTER_COUNT];

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

uint16_t get_sensor_filtered(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    return LECTURA_MAXIMO_SENSORES_LINEA - sensors_filtered[index];
  } else {
    return sensors_filtered[index];
  }
}

uint16_t get_sensor_calibrated(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    if (get_sensor_raw(index) > LINE_SENSOR_THRESHOLD) {
      return LECTURA_MAXIMO_SENSORES_LINEA;
    } else {
      return LECTURA_MINIMO_SENSORES_LINEA;
    }
  } else {
    if (get_sensor_raw(index) > RIVAL_SENSOR_THRESHOLD && get_sensor_raw(index) < RIVAL_SENSOR_MAX) {
      return get_sensor_raw(index);
    } else {
      return 0;
    }
  }
}

bool get_sensor_digital(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    if (get_sensor_filtered(index) > LINE_SENSOR_THRESHOLD) {
      return true;
    }
  } else {
    if (get_sensor_filtered(index) > RIVAL_SENSOR_THRESHOLD && get_sensor_filtered(index) < RIVAL_SENSOR_MAX) {
      return true;
    }
  }
  return false;
}

void update_sensors_readings(void) {
  // for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
  //   if (sensor == SENSOR_LINE_LEFT || sensor == SENSOR_LINE_RIGHT) {
  //     sensors_filtered[sensor] = sensors_raw[sensor];
  //   } else {
  //     sensors_filtered[sensor] = 0.993 * sensors_filtered[sensor] + 0.0031 * sensors_raw[sensor] + 0.0031 * sensors_last_raw[sensor];
  //     sensors_last_raw[sensor] = sensors_raw[sensor];
  //   }
  // }

  for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
    sensors_filter[sensor][sensors_filter_index] = sensors_raw[sensor];

    uint32_t sum_filter_sensor = 0;
    for (uint8_t i = 0; i < SENSORS_FILTER_COUNT; i++) {
      sum_filter_sensor += sensors_filter[sensor][i];
    }
    sensors_filtered[sensor] = sum_filter_sensor / SENSORS_FILTER_COUNT;
  }
  sensors_filter_index = (sensors_filter_index + 1) % SENSORS_FILTER_COUNT;
}

void update_sensors_position(void) {
  uint32_t sensor_avg = 0;
  uint32_t sensor_sum = 0;
  uint8_t sensor_detecting = 0;
  for (uint8_t sensor = 0; sensor < NUM_SENSORS - NUM_SENSORS_LINE; sensor++) {
    sensors_digital[sensor] = get_sensor_digital(sensor + 1);
    sensors_weight[sensor] = sensors_digital[sensor] ? 100 : 0;
    // sensors_weight[sensor] = sensors_digital[sensor] ? map(sensors_raw[sensor + 1], RIVAL_SENSOR_THRESHOLD, RIVAL_SENSOR_MAX, 1, 100) : 0;

    if (sensors_digital[sensor]) {
      sensor_avg += sensors_weight[sensor] * (sensor + 1) * 100;
      sensor_sum += sensors_weight[sensor];
      sensor_detecting++;
    }
  }
  if (sensor_detecting > 0) {
    // printf(" > %ld - %ld |", sensor_avg, sensor_sum);
    sensors_position = (sensor_avg / sensor_sum - ((100 * (NUM_SENSORS - NUM_SENSORS_LINE + 1)) / 2));
    // printf("%d ", -3500);
    // printf("%d ", 3500);
    // printf("%d\n", sensors_position);
  } else if (sensors_position > 0) {
    sensors_position = 300;
  } else {
    sensors_position = -300;
  }
}

int16_t get_sensors_position(void) {
  return sensors_position;
}