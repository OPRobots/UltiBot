#include "control.h"

static bool competicionIniciada = false;
static enum STATUS last_state;
static enum STATUS current_state = STATE_OPENING;
static enum OPENINGS current_opening = OPENING_FRONT;
static enum STRATS current_strat = STRAT_KEEPING_INSIDE; // TODO: actualizar estrategia por defecto

static uint32_t current_state_timer = 0;
static uint32_t current_strat_timer = 0;

static void set_state(enum STATUS state) {
  last_state = current_state;
  current_state = state;
  current_state_timer = get_clock_ticks();
}

static void check_outter_line(void) {
  if (current_state != STATE_KEEPING_INSIDE && (get_sensor_calibrated(SENSOR_LINE_LEFT) < LINE_SENSOR_THRESHOLD || get_sensor_calibrated(SENSOR_LINE_RIGHT) < LINE_SENSOR_THRESHOLD)) {
    set_state(STATE_KEEPING_INSIDE);
  }
}

static void keeping_inside(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 200) {
    set_motors_speed(-100, -100);
  } else if (time <= 400) {
    set_motors_speed(100, -100);
  } else {
    // TODO: comprobar si no hay problemas de referencias al asignar lo mismo que se está modificando justo dentro
    set_state(last_state);
  }
}

static void opening_front(void) {
}

static void opening_right(void) {
}

static void opening_left(void) {
}

static void opening_back(void) {
}

/**
 * @brief Estrategia simple evitando salirse del dohyo, ignorando valor de sensores
 *
 */
static void strat_keeping_inside(void) {
  set_motors_speed(50, 50);
  // La gestión de mantenerse en el dohyo se realiza por defecto mediante check_outter_line(void) y keeping_inside(void)
}

/**
 * @brief Comprueba si el robot está en funcionamiento
 *
 * @return bool
 */

bool is_competicion_iniciada(void) {
  return competicionIniciada;
}

/**
 * @brief Establece si la competición se ha iniciado y estado actual del robot
 *
 * @param iniciado Estado actual del robot
 */

void set_competicion_iniciada(bool iniciado) {
  competicionIniciada = iniciado;
  if (iniciado) {
    set_state(STATE_OPENING);
  }
}

/**
 * @brief Establece la estrategia de inicio
 *
 * @param OPENINGS opening
 */
void set_opening(enum OPENINGS opening) {
  current_opening = opening;
}

/**
 * @brief Establece la estrategia actual
 *
 * @param STRATS strat
 */
void set_strat(enum STRATS strat) {
  current_strat = strat;
  current_strat_timer = get_clock_ticks();
}

/**
 * @brief Función principal de control que se llama en el Systick cada 1ms
 * TODO: mover a ISR independiente para no perjudicar la gestión de los leds
 *
 */
void control_main_loop(void) {
  if (is_competicion_iniciada()) {
    check_outter_line();
    switch (current_state) {
      case STATE_RUNNING:
        switch (current_strat) {
          case STRAT_KEEPING_INSIDE:
            strat_keeping_inside();
            break;
          default:
            // TODO: definir una estrategia por defecto en caso de error?
            set_fatal_error_rgb();
            set_motors_speed(0, 0);
            break;
        }
        break;
      case STATE_OPENING:
        switch (current_opening) {
          case OPENING_FRONT:
            opening_front();
            break;
          case OPENING_RIGHT:
            opening_right();
            break;
          case OPENING_LEFT:
            opening_left();
            break;
          case OPENING_BACK:
            opening_back();
            break;
          default:
            // TODO: definir una apertura por defecto en caso de error?
            set_fatal_error_rgb();
            set_motors_speed(0, 0);
            break;
        }
        break;
      case STATE_KEEPING_INSIDE:
        keeping_inside();
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