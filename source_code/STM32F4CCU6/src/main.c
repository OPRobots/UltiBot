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

void sys_tick_handler(void) {
  clock_tick();
  update_sensors_readings();
}

int main(void) {
  setup();

  while (true) {
    // debug_sensors_leds();
    // debug_sensors_calibrated();
    // debug_sensors_position();
    // // // printf("%d ", get_sensor_raw(SENSOR_FRONT_LEFT));
    // // // printf("%d\n", get_sensor_filtered(SENSOR_FRONT_LEFT));
    // delay(25);
    // continue;

    if (!is_competicion_iniciada()) {
      check_menu_button();
      // debug_sensors_leds();
      if (get_start_btn()) {
        set_sensor_led(false);
        set_menu_led(false);
        while (get_start_btn()) {
          set_sensor_led_waiting(100);
        }
        uint32_t millisInicio = get_clock_ticks();
        while (get_clock_ticks() < (millisInicio + get_start_millis())) {
          set_sensor_led_starting(millisInicio);
        }
        set_sensor_led(false);
        set_competicion_iniciada(true);
        send_command(CMD_MOTOR_ENABLE, 0);
      }
    } else {
      control_main_loop();
    }
  }
  return 0;
}