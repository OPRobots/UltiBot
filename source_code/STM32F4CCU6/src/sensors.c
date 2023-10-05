#include "sensors.h"

static uint8_t sensors_adc[NUM_SENSORS] = {ADC_CHANNEL7, ADC_CHANNEL6, ADC_CHANNEL3, ADC_CHANNEL5, ADC_CHANNEL2, ADC_CHANNEL4, ADC_CHANNEL1, ADC_CHANNEL0};
static volatile uint16_t sensors_raw[NUM_SENSORS];

static bool sensors_digital[NUM_SENSORS];
static uint8_t sensors_digital_count[NUM_SENSORS];
static uint16_t sensors_calibrated[NUM_SENSORS];
static uint16_t sensors_filtered[NUM_SENSORS];
static int16_t sensors_position = 0;

static uint8_t sensors_filter_index = 0;
static uint16_t sensors_filter[NUM_SENSORS][SENSORS_FILTER_COUNT];

static bool rival_close = false;
static uint32_t rival_close_ms = 0;

static void update_sensors(void) {
  for (uint8_t sensor = 0; sensor < NUM_SENSORS; sensor++) {
    sensors_filter[sensor][sensors_filter_index] = get_sensor_raw(sensor);

    uint32_t sum_filter = 0;
    for (uint8_t filter = 0; filter < SENSORS_FILTER_COUNT; filter++) {
      sum_filter += sensors_filter[sensor][filter];
    }
    sensors_filtered[sensor] = sum_filter / SENSORS_FILTER_COUNT;

    if (sensor == SENSOR_LINE_LEFT || sensor == SENSOR_LINE_RIGHT) {
      sensors_calibrated[sensor] = sensors_filtered[sensor] > LINE_SENSOR_THRESHOLD ? LECTURA_MAXIMO_SENSORES_LINEA : LECTURA_MINIMO_SENSORES_LINEA;

      if (sensors_calibrated[sensor] >= LINE_SENSOR_THRESHOLD) {
        if (sensors_digital_count[sensor] >= SENSOR_LINE_DIGITAL_COUNT) {
          sensors_digital[sensor] = true;
        } else {
          sensors_digital[sensor] = false;
          sensors_digital_count[sensor]++;
        }
      } else {
        sensors_digital[sensor] = false;
        sensors_digital_count[sensor] = 0;
      }
    } else {
      if (sensors_filtered[sensor] >= RIVAL_SENSOR_THRESHOLD) {
        if (sensors_filtered[sensor] > RIVAL_SENSOR_MAX) {
          sensors_calibrated[sensor] = RIVAL_SENSOR_MAX;
        } else {
          sensors_calibrated[sensor] = sensors_filtered[sensor];
        }
      } else {
        sensors_calibrated[sensor] = 0;
      }

      if (sensors_calibrated[sensor] > RIVAL_SENSOR_THRESHOLD) {
        if (sensors_digital_count[sensor] >= SENSOR_DIGITAL_COUNT) {
          sensors_digital[sensor] = true;
        } else {
          sensors_digital[sensor] = false;
          sensors_digital_count[sensor]++;
        }
      } else {
        sensors_digital[sensor] = false;
        sensors_digital_count[sensor] = 0;
      }
    }
  }

  if (sensors_calibrated[SENSOR_FRONT_LEFT] >= RIVAL_SENSOR_CLOSE_THRESHOLD || sensors_calibrated[SENSOR_FRONT_RIGHT] >= RIVAL_SENSOR_CLOSE_THRESHOLD || sensors_calibrated[SENSOR_ANGLE_LEFT] >= RIVAL_SENSOR_CLOSE_THRESHOLD || sensors_calibrated[SENSOR_ANGLE_RIGHT] >= RIVAL_SENSOR_CLOSE_THRESHOLD) {
    if (!rival_close) {
      rival_close_ms = get_clock_ticks();
    }
    rival_close = true;
  } else {
    if (rival_close) {
      rival_close_ms = get_clock_ticks();
    }
    rival_close = false;
  }

  sensors_filter_index = (sensors_filter_index + 1) % SENSORS_FILTER_COUNT;
}

static void update_sensors_position(void) {
  uint32_t sensor_avg = 0;
  uint32_t sensor_sum = 0;
  uint8_t sensor_detecting = 0;
  for (uint8_t sensor = 1; sensor < NUM_SENSORS - NUM_SENSORS_LINE / 2; sensor++) {
    if (get_sensor_digital(sensor)) {
      sensor_avg += (sensor)*RIVAL_SENSOR_MAX /* get_sensor_calibrated(sensor) */ * 100;
      sensor_sum += RIVAL_SENSOR_MAX /* get_sensor_calibrated(sensor) */;
      sensor_detecting++;
    }
  }
  if (sensor_detecting > 0) {
    // printf(" > %ld - %ld |", sensor_avg, sensor_sum);
    sensors_position = (sensor_avg / sensor_sum - ((100 * (NUM_SENSORS - NUM_SENSORS_LINE + 1)) / 2));
    // printf("%d ", -3500);
    // printf("%d ", 3500);
    // printf("%d\n", sensors_position);
  } else if (sensors_position > 75) {
    sensors_position = 300;
  } else if (sensors_position < -75) {
    sensors_position = -300;
  }
}

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
    // Cambia la lógica de los sensores de línea
    return LECTURA_MAXIMO_SENSORES_LINEA - sensors_raw[index];
  } else {
    return sensors_raw[index];
  }
}

uint16_t get_sensor_calibrated(enum SENSORS index) {
  return sensors_calibrated[index];
}

bool get_sensor_digital(enum SENSORS index) {
  return sensors_digital[index];
}

int16_t get_sensors_position(void) {
  return sensors_position;
}

bool is_rival_close(void) {
  return rival_close;
}

uint32_t get_rival_close_ms(void) {
  return rival_close_ms;
}

void update_sensors_readings(void) {
  update_sensors();
  update_sensors_position();
}