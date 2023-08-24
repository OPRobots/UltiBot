#include "control.h"

static bool competicionIniciada = false;
static enum STATUS last_state;
static enum STATUS current_state = STATE_OPENING;
static enum OPENINGS current_opening = OPENING_FRONT;
static enum STRATS current_strat = STRAT_KEEPING_INSIDE; // TODO: actualizar estrategia por defecto

static unsigned long current_state_timer = 0;
static unsigned long current_strat_timer = 0;
static bool current_strat_state = false;
static int current_strat_count = 0;

static void set_state(enum STATUS state) {
  last_state = current_state;
  current_state = state;
  current_state_timer = millis();
}

static void check_outter_line(void) {
  if (current_state != STATE_KEEPING_INSIDE && (get_sensor_digital(SENSOR_LINE_LEFT) || get_sensor_digital(SENSOR_LINE_RIGHT))) {
    set_state(STATE_KEEPING_INSIDE);
  }
}

static void keeping_inside(void) {
  unsigned long time = millis() - current_state_timer;
  if (time <= 180) {
    set_speed(-100, -100);
  } else if (time <= 180 + 160) {
    set_speed(100, -100);
  } else {
    set_state(last_state);
  }
}

static void opening_front(void) {
  set_state(STATE_RUNNING);
}

static void opening_right(void) {
  set_speed(100, -100);
  if (millis() > current_state_timer + 100) {
    set_state(STATE_RUNNING);
  }
}

static void opening_left(void) {
  set_speed(-100, 100);
  if (millis() > current_state_timer + 125) {
    set_state(STATE_RUNNING);
  }
}

static void opening_back(void) {
  set_speed(100, -100);
  if (millis() > current_state_timer + 180) {
    set_state(STATE_RUNNING);
  }
}

/**
 * @brief Estrategia simple evitando salirse del dohyo, ignorando valor de sensores
 *
 */
static void strat_keeping_inside(void) {
  set_speed(0, 0);
  // La gestión de mantenerse en el dohyo se realiza por defecto mediante check_outter_line(void) y keeping_inside(void)
}

static float strat_search_follow_kp = 1;
static float strat_search_follow_kd = 2.5f;
static int strat_search_follow_last_error = 0;
static unsigned int strat_search_follow_last_time = 0;
/**
 * @brief Estrategia estática encarando el robot rival
 *
 */
static void strat_search_follow(void) {
  if (millis() > strat_search_follow_last_time + 20) {
    strat_search_follow_last_time = millis();
    int pos = get_sensor_position();
    int pid = strat_search_follow_kp * pos + strat_search_follow_kd * (pos - strat_search_follow_last_error);
    strat_search_follow_last_error = pos;
    set_speed(50+pid, 50-pid);
  }
}

/**
 * @brief Estrategia de movimientos cortos
 * 
 */
static void strat_chiquito_steps(void) {
  if (current_strat_state) {
    if (millis() > current_strat_timer + 3000) {
      set_speed(50, 50);
      current_strat_count++;
      current_strat_state = !current_strat_state;
      current_strat_timer = millis();
    }
  } else {
    if (millis() > current_strat_timer + 50) {
      set_speed(0, 0);
      current_strat_state = !current_strat_state;
      current_strat_timer = millis();
    }
  }
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
    current_state_timer = millis();
    current_strat_timer = millis();
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
  current_strat_timer = millis();
  current_strat_state = false;
  current_strat_count = 0;
}

/**
 * @brief Función principal de control que se llama en el Systick cada 1ms
 * TODO: mover a ISR independiente para no perjudicar la gestión de los leds
 *
 */
void control_main_loop(void) {
  if (is_competicion_iniciada()) {
    update_sensors_readings();
    check_outter_line();
    switch (current_state) {
      case STATE_RUNNING:
        switch (current_strat) {
          case STRAT_KEEPING_INSIDE:
            strat_keeping_inside();
            break;
          case STRAT_SEARCH_FOLLOW:
            strat_search_follow();
            break;
          case STRAT_CHIQUITO_STEPS:
            strat_chiquito_steps();
            break;
          default:
            // TODO: definir una estrategia por defecto en caso de error?
            set_leds_fatal_error();
            set_speed(0, 0);
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
            set_leds_fatal_error();
            set_speed(0, 0);
            break;
        }
        break;
      case STATE_KEEPING_INSIDE:
        keeping_inside();
        break;
      default:
        set_leds_fatal_error();
        set_speed(0, 0);
        break;
    }

  } else {
    set_speed(0, 0);
  }
}