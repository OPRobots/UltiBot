#include "control.h"

static bool competicionIniciada = false;
static enum STATUS last_state;
static enum STATUS current_state = STATE_OPENING;
static enum OPENINGS current_opening = OPENING_FRONT;
static enum STRATS current_strat = STRAT_PID; // TODO: actualizar estrategia por defecto

static uint32_t current_state_timer = 0;
static uint32_t current_strat_timer = 0;

static uint32_t strat_pid_last_ms = 0;
static int16_t strat_pid_last_error = 0;

static void set_state(enum STATUS state) {
  last_state = current_state;
  current_state = state;
  current_state_timer = get_clock_ticks();
}

static void check_outter_line(void) {
  if (current_state != STATE_KEEPING_INSIDE && (get_sensor_digital(SENSOR_LINE_LEFT) || get_sensor_digital(SENSOR_LINE_RIGHT))) {
    set_state(STATE_KEEPING_INSIDE);
  }
}

static void keeping_inside(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 200) {
    set_motors_speed(-TURN_SPEED, -TURN_SPEED);
  } else if (time <= 600 && !is_rival_detected()) {
    set_motors_speed(TURN_SPEED, -TURN_SPEED);
  } else {
    // TODO: comprobar si no hay problemas de referencias al asignar lo mismo que se está modificando justo dentro
    set_state(last_state);
  }
}

static void opening_front(void) {
  set_state(STATE_RUNNING);
}

static void opening_right(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 240 && !is_rival_detected()) {
    set_motors_speed(80, -80);
  } else {
    // set_motors_speed(0, 0);
    // if (time >= 600) {
    //   send_command(CMD_MOTOR_DISABLE, 0);
    // }
    set_state(STATE_RUNNING);
  }
}

static void opening_right_arc(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 650 && !is_rival_detected()) {
    set_motors_speed(90, 20);
  } else {
    // set_motors_speed(0, 0);
    // if (time >= 600) {
    //   send_command(CMD_MOTOR_DISABLE, 0);
    // }
    set_state(STATE_RUNNING);
  }
}

static void opening_left(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 240 && !is_rival_detected()) {
    set_motors_speed(-80, 80);
  } else {
    // set_motors_speed(0, 0);
    // if (time >= 600) {
    //   send_command(CMD_MOTOR_DISABLE, 0);
    // }
    set_state(STATE_RUNNING);
  }
}

static void opening_left_arc(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 650 && !is_rival_detected()) {
    set_motors_speed(20, 90);
  } else {
    // set_motors_speed(0, 0);
    // if (time >= 600) {
    //   send_command(CMD_MOTOR_DISABLE, 0);
    // }
    set_state(STATE_RUNNING);
  }
}

static void opening_back(void) {
  uint32_t time = get_clock_ticks() - current_state_timer;
  if (time <= 490 && !is_rival_detected()) {
    set_motors_speed(80, -80);
  } else {
    // set_motors_speed(0, 0);
    // if (time >= 800) {
    //   send_command(CMD_MOTOR_DISABLE, 0);
    // }
    set_state(STATE_RUNNING);
  }
}

/**
 * @brief Estrategia simple evitando salirse del dohyo, ignorando valor de sensores
 *
 */
static void strat_keeping_inside(void) {
  set_motors_speed(BASE_SPEED, BASE_SPEED);
  // La gestión de mantenerse en el dohyo se realiza por defecto mediante check_outter_line(void) y keeping_inside(void)
}

/**
 * @brief Estrategia que busca y persigue el rival, usando posición dinámica de sensores
 *
 */
static void strat_pid(void) {
  // TODO: quitar este if si se pasa la función principal a un ISR a 1ms
  if (get_clock_ticks() - strat_pid_last_ms > 1) {
    debug_sensors_leds();
    int16_t error = get_sensors_position();
    int correccion = error * STRAT_PID_KP + (error - strat_pid_last_error) * STRAT_PID_KD;

    strat_pid_last_error = error;
    // printf("%d | %d | ", error, correccion);
    set_motors_speed(BASE_SPEED + correccion, BASE_SPEED - correccion);
    strat_pid_last_ms = get_clock_ticks();

    if (get_rival_close_ms() != 0) {
      uint32_t ms_diff = get_clock_ticks() - get_rival_close_ms();
      if (ms_diff > 250) {
        if (ms_diff < 1000) {
          // send_command(CMD_CONFIG_SINE_STEP, is_rival_close() ? 4 : 2);
        } else if (ms_diff < 1500) {
          // send_command(CMD_CONFIG_SINE_STEP, is_rival_close() ? 3 : 3);
        } else if (ms_diff < 2000) {
          // send_command(CMD_CONFIG_SINE_STEP, is_rival_close() ? 2 : 4);
        } else if (ms_diff < 2500) {
          // send_command(CMD_CONFIG_SINE_STEP, is_rival_close() ? 1 : 5);
        }
      }
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
 * @brief Obtiene la estrategia de inicio
 *
 * @param OPENINGS opening
 */
enum OPENINGS get_opening(void) {
  return current_opening;
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
 * @brief Obtiene la estrategia actual
 *
 * @param STRATS strat
 */
enum STRATS get_strat(void) {
  return current_strat;
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
        set_menu_led(true);
        switch (current_strat) {
          case STRAT_KEEPING_INSIDE:
            strat_keeping_inside();
            break;
          case STRAT_PID:
            strat_pid();
            break;
          default:
            // TODO: definir una estrategia por defecto en caso de error?
            // TODO: set_fatal_error_rgb();
            set_motors_speed(0, 0);
            break;
        }
        break;
      case STATE_OPENING:
        set_menu_led_blink(50);
        switch (current_opening) {
          case OPENING_FRONT:
            opening_front();
            break;
          case OPENING_RIGHT:
            opening_right();
            break;
          case OPENING_RIGHT_ARC:
            opening_right_arc();
            break;
          case OPENING_LEFT:
            opening_left();
            break;
          case OPENING_LEFT_ARC:
            opening_left_arc();
            break;
          case OPENING_BACK:
            opening_back();
            break;
          default:
            // TODO: definir una apertura por defecto en caso de error?
            // TODO: set_fatal_error_rgb();
            set_motors_speed(0, 0);
            break;
        }
        break;
      case STATE_KEEPING_INSIDE:
        keeping_inside();
        set_menu_led_blink(125);
        break;
      default:
        set_motors_speed(0, 0);
        break;
    }

  } else {
    set_motors_speed(0, 0);
  }
}