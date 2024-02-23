#include "command.h"
#include "config.h"
#include "control.h"
#include "debug.h"
#include "delay.h"
#include "leds.h"
#include "menu.h"
#include "motors.h"
#include "sensors.h"
#include "setup.h"
#include "usart.h"
#include "eeprom.h"
#include "rc5.h"

void sys_tick_handler(void) {
  clock_tick();
  update_sensors_readings();
}

int main(void) {
  setup();
  eeprom_load();
  rc5_init();

  while (true) {
    // debug_sensors_leds();
    // debug_sensors_raw();
    // // debug_sensors_position();
    // // printf("%d - %d\n", get_sensor_digital(SENSOR_LINE_LEFT), get_sensor_digital(SENSOR_LINE_RIGHT));
    // // // // // printf("%d\n", get_sensor_filtered(SENSOR_FRONT_LEFT));
    // // delay(25);

    // // send_command(CMD_MOTOR_SPEED_RIGHT, 40);
    // // send_command(CMD_MOTOR_SPEED_LEFT, 40);
    // // send_command(CMD_MOTOR_ENABLE, 0);
    // // delay(15000);
    // // send_command(CMD_MOTOR_SPEED_RIGHT, 0);
    // // send_command(CMD_MOTOR_SPEED_LEFT, 0);
    // // send_command(CMD_MOTOR_DISABLE, 0);
    // // delay(2000);

    // // if (get_start_btn()) {
    // //   send_command(CMD_MOTOR_DISABLE, 0);
    // //   send_command(CMD_MOTOR_SPEED_RIGHT, 40);
    // //   send_command(CMD_MOTOR_SPEED_LEFT, 40);
    // // } else {
    // //   send_command(CMD_MOTOR_ENABLE, 0);
    // //   send_command(CMD_MOTOR_SPEED_RIGHT, 20);
    // //   send_command(CMD_MOTOR_SPEED_LEFT, 20);
    // // }
    // // printf("pato\n");
    // // printf("%ld\n", get_us_counter());
    // delay(100);

    // continue;

    if (!is_competicion_iniciada() && !is_competicion_iniciando()) {
      check_menu_button();
      // debug_sensors_leds();
      if (get_start_btn()) {
        set_sensor_led(false);
        set_menu_led(false);
        while (get_start_btn()) {
          set_sensor_led_waiting(100);
        }
        set_competicion_iniciando(true);
      }
    } else if (is_competicion_iniciando()) {
      uint32_t millisInicio = get_clock_ticks();
      while (get_clock_ticks() < (millisInicio + get_start_millis()) && is_competicion_iniciando()) {
        set_sensor_led_starting(millisInicio);
      }
      if (is_competicion_iniciando()) {
        set_sensor_led(false);
        set_competicion_iniciada(true);
        send_command(CMD_MOTOR_ENABLE, 0);
      }
    } else {
      debug_sensors_leds();
      control_main_loop();
    }
  }
  return 0;
}