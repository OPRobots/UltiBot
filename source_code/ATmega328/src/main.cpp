#include "buttons.h"
#include "commons.h"
#include "constants.h"
#include "control.h"
#include "debug.h"
#include "leds.h"
#include "menu.h"

void init_peripheals() {
  Serial.begin(9600);

  pinMode(LED_DER, OUTPUT);
  pinMode(LED_CEN, OUTPUT);
  pinMode(LED_IZQ, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);

  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_MENU_UP, INPUT_PULLUP);
  pinMode(BTN_MENU_DO, INPUT_PULLUP);
  pinMode(BTN_MENU_MO, INPUT_PULLUP);

  pinMode(SENSOR_LAT_DER, INPUT);
  pinMode(SENSOR_ANG_DER, INPUT);
  pinMode(SENSOR_FRO_DER, INPUT);
  pinMode(SENSOR_LIN_DER, INPUT);
  pinMode(SENSOR_LIN_IZQ, INPUT);
  pinMode(SENSOR_FRO_IZQ, INPUT);
  pinMode(SENSOR_ANG_IZQ, INPUT);
  pinMode(SENSOR_LAT_IZQ, INPUT);

  pinMode(MOTOR_DER_A, OUTPUT);
  pinMode(MOTOR_DER_B, OUTPUT);
  pinMode(MOTOR_IZQ_A, OUTPUT);
  pinMode(MOTOR_IZQ_B, OUTPUT);

  // Pins D9 and D10 - 976 Hz
  TCCR1A = 0b00000001; // 8bit
  TCCR1B = 0b00001011; // x64 fast pwm

  // Pins D3 and D11 - 980 Hz
  TCCR2B = 0b00000100; // x64
  TCCR2A = 0b00000011; // fast pwm

  analogWrite(MOTOR_DER_A, MAX_PWM);
  analogWrite(MOTOR_DER_B, MAX_PWM);
  analogWrite(MOTOR_IZQ_A, MAX_PWM);
  analogWrite(MOTOR_IZQ_B, MAX_PWM);
}

void setup() {
  // Iniciar pines, sensores, etc.
  init_peripheals();
}

void loop() {
  if (!is_competicion_iniciada()) {
    handle_menu();
    if (get_start_btn()) {
      reset_menu();
      while (get_start_btn()) {
        set_leds(true);
      }
      unsigned long millisInicio = millis();
      while (millis() - millisInicio < MILLIS_INICIO) {
        int millisPasados = millis() - millisInicio;
        if (millisPasados < 2000) {
          set_leds_fatal_error();
        } else if (millisPasados < 3000) {
          set_leds(true);
        } else if (millisPasados < 4000) {
          set_led_right(true);
          set_led_center(false);
          set_led_left(true);
        } else if (millisPasados < 5000) {
          set_led_right(false);
          set_led_center(true);
          set_led_left(false);
        }
      }
      set_leds(false);
      set_competicion_iniciada(true);
    }

    // debugIO();
    // update_sensors_readings();
    // delay(100);
    // debug_sensors_calibrated();
    // debug_sensors_raw();
    // debug_sensors_position();

  } else {
    control_main_loop();
  }
}
