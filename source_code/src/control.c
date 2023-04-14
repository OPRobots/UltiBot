#include "control.h"

static bool competicionIniciada = false;
static enum STRATS current_strat;

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
 * @brief Estrategia simple evitando salirse del dohyo, ignorando valor de sensores
 *
 */
static void strat_keeping_inside(void) {
  set_motors_speed(50, 50);
  if (get_sensor_calibrated(SENSOR_LINE_LEFT) < LINE_SENSOR_THRESHOLD || get_sensor_calibrated(SENSOR_LINE_RIGHT) < LINE_SENSOR_THRESHOLD) {
    set_motors_speed(-100, -100);
    delay(200);
    set_motors_speed(100, -100);
    delay(200);
  }
}

/**
 * @brief Establece la estrategia actual
 *
 * @param STRATS strat
 */
void set_strat(enum STRATS strat) {
  current_strat = strat;
}

/**
 * @brief Función principal de control que se llama en el Systick cada 1ms
 * TODO: mover a ISR independiente para no perjudicar la gestión de los leds
 *
 */
void control_main_loop(void) {
  if (is_competicion_iniciada()) {
    switch (current_strat) {
      case STRAT_KEEPING_INSIDE:
        strat_keeping_inside();
        break;
      default:
        set_fatal_error_rgb();
        set_motors_speed(0, 0);
        break;
    }

  } else {
    set_motors_speed(0, 0);
  }
}