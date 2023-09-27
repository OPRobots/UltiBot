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
}

int main(void) {
  setup();

  while (1) {
    for (int i = 0; i < get_sensors_num(); i++) {
      printf("%d: %d\t", i, get_sensor_raw(i));
    }
    printf("btn: %d\t", get_start_btn());
    printf("\n");
    // debug_sensors();
    delay(50);

    if (get_start_btn()) {
      send_command(CMD_MOTOR_SPEED_LEFT, 50);
      send_command(CMD_MOTOR_SPEED_RIGHT, 50);
      send_command(CMD_MOTOR_ENABLE, 0);
      // delay(5000);

    } else {

      send_command(CMD_MOTOR_SPEED_LEFT, 0);
      send_command(CMD_MOTOR_SPEED_RIGHT, 0);
      send_command(CMD_MOTOR_DISABLE, 0);
    }

    continue;

    if (!gpio_get(GPIOA, GPIO0)) {
      gpio_clear(GPIOC, GPIO13);
      // send_command(CMD_MOTOR_ENABLE, 0);
      // send_command(CMD_MOTOR_SPEED_LEFT, 50);
      // send_command(CMD_MOTOR_SPEED_RIGHT, 50);
      while (!gpio_get(GPIOA, GPIO0)) {
      }
    } else {
      gpio_set(GPIOC, GPIO13);
      // send_command(CMD_MOTOR_DISABLE, 0);
    }

    continue;
    if (!is_competicion_iniciada()) {
      // TODO: menu
      if (get_start_btn()) {
        // TODO: reset menu mode
        while (get_start_btn()) {
          // TODO: set_rgb(LED_CENTER, 0, 0, 50);
        }
        uint32_t millisInicio = get_clock_ticks();
        // uint16_t millisPasados = 5;
        while (get_clock_ticks() < (millisInicio + get_start_millis())) {
          // millisPasados = get_clock_ticks() - millisInicio;
          // uint8_t r = 0, g = 0;
          // r = map(millisPasados, 0, get_start_millis(), 255, 0);
          // g = map(millisPasados, 0, 1000, 0, 255);
          // TODO: set_rgb(LED_CENTER, r, g, 0);
        }
        // TODO: set_rgb(LED_CENTER, 0, 0, 0);
        set_competicion_iniciada(true);
      }
    }

    control_main_loop();

    // set_motors_speed(-30, -30);
    // delay(2000);
    // set_motors_speed(0, 0);
    // delay(5000);
    // set_motors_speed(-50, -50);
    // delay(1000);
    // set_motors_speed(50, -50);
    // delay(1000);
    // set_motors_speed(-50, 50);
    // delay(1000);
    // set_motors_speed(-50, -50);
    // delay(1000);

    // for(int i = 0; i< get_sensors_num(); i++){
    //   printf("%d: %d\t", i, get_sensor_raw(i));
    // }
    // printf("btn: %d\t", get_start_btn());
    // printf("\n");
    debug_sensors();
    delay(50);
  }
  return 0;
}