#include "sensors.h"

static uint8_t sensors_adc[NUM_SENSORS] = {ADC_CHANNEL0, ADC_CHANNEL1, ADC_CHANNEL2, ADC_CHANNEL3, ADC_CHANNEL4, ADC_CHANNEL5, ADC_CHANNEL6, ADC_CHANNEL7};
static volatile uint16_t sensors_raw[NUM_SENSORS];

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
  return sensors_raw[index];
}

uint16_t get_sensor_calibrated(enum SENSORS index) {
  if (index == SENSOR_LINE_LEFT || index == SENSOR_LINE_RIGHT) {
    if (sensors_raw[index] > LINE_SENSOR_THRESHOLD) {
      return LECTURA_MAXIMO_SENSORES_LINEA;
    } else {
      return LECTURA_MINIMO_SENSORES_LINEA;
    }
  } else {
    if (sensors_raw[index] > RIVAL_SENSOR_THRESHOLD) {
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
    if (sensors_raw[index] > RIVAL_SENSOR_THRESHOLD) {
      return true;
    }
  }
  return false;
}
