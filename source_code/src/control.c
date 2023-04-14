#include "control.h"

static bool competicionIniciada = false;

/**
 * @brief Comprueba si el robot está en funcionamiento
 *
 * @return bool
 */

bool is_competicion_iniciada(void) {
  return competicionIniciada;
}

/**
 * @brief Establece el estado actual del robot
 *
 * @param state Estado actual del robot
 */

void set_competicion_iniciada(bool state) {
  competicionIniciada = state;
}

/**
 * @brief Función principal de control que se llama en el Systick cada 1ms
 *
 */
void control_main_loop(void) {
  if (is_competicion_iniciada()) {
    set_motors_speed(50, 50);
    if (get_sensor_calibrated(SENSOR_LINE_LEFT) < LINE_SENSOR_THRESHOLD || get_sensor_calibrated(SENSOR_LINE_RIGHT) < LINE_SENSOR_THRESHOLD) {
      set_motors_speed(-50, -50);
      delay(200);
      set_motors_speed(-50, 50);
      delay(300);
    }
  } else {
    set_motors_speed(0, 0);
  }
}