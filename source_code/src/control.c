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
}