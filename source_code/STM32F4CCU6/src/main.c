#include "command.h"
#include "config.h"
#include "control.h"
#include "debug.h"
#include "delay.h"
#include "leds.h"
#include "motors.h"
#include "sensors.h"
#include "setup.h"
#include "usart.h"

void sys_tick_handler(void) {
  clock_tick();
  update_sensors_readings();
  update_sensors_position();
}

int main(void) {
  setup();

  while (true) {
    if (!is_competicion_iniciada()) {
      // TODO: menu
      if (get_start_btn()) {
        set_sensor_led(false);
        while (get_start_btn()) {
          set_sensor_led_waiting(100);
        }
        uint32_t millisInicio = get_clock_ticks();
        while (get_clock_ticks() < (millisInicio + get_start_millis())) {
          set_sensor_led_starting(millisInicio);
        }
        set_sensor_led(false);
        set_competicion_iniciada(true);
      }
    } else {
      // control_main_loop();
    }
  }
  return 0;
}