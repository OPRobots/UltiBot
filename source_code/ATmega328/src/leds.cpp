#include "leds.h"

static unsigned long fatal_error_timer = 0;
static unsigned long led_status_warning_timer = 0;
static unsigned long led_left_warning_timer = 0;
static unsigned long led_center_warning_timer = 0;
static unsigned long led_right_warning_timer = 0;
static bool fatal_error_state = false;

void set_leds(bool state) {
  set_led_left(state);
  set_led_center(state);
  set_led_right(state);
}

void set_leds_fatal_error(void) {
  if (millis() > fatal_error_timer + 50) {
    set_leds(fatal_error_state);
    fatal_error_timer = millis();
    fatal_error_state = !fatal_error_state;
  }
}

void set_led_left(bool state) {
  digitalWrite(LED_DER, state);
}

void set_led_center(bool state) {
  digitalWrite(LED_CEN, state);
}

void set_led_right(bool state) {
  digitalWrite(LED_IZQ, state);
}

void set_led_left_warning(unsigned int ms) {
  if (millis() - led_left_warning_timer > ms * 2) {
    digitalWrite(LED_DER, HIGH);
    led_left_warning_timer = millis();
  }
  if (millis() > led_left_warning_timer + ms) {
    digitalWrite(LED_DER, !digitalRead(LED_DER));
    led_left_warning_timer = millis();
  }
}

void set_led_center_warning(unsigned int ms) {
  if (millis() - led_center_warning_timer > ms * 2) {
    digitalWrite(LED_CEN, HIGH);
    led_center_warning_timer = millis();
  }
  if (millis() > led_center_warning_timer + ms) {
    digitalWrite(LED_CEN, !digitalRead(LED_CEN));
    led_center_warning_timer = millis();
  }
}

void set_led_right_warning(unsigned int ms) {
  if (millis() - led_right_warning_timer > ms * 2) {
    digitalWrite(LED_IZQ, HIGH);
    led_right_warning_timer = millis();
  }
  if (millis() > led_right_warning_timer + ms) {
    digitalWrite(LED_IZQ, !digitalRead(LED_IZQ));
    led_right_warning_timer = millis();
  }
}

void set_led_status(bool state) {
  digitalWrite(LED_STATUS, state);
}

void set_led_status_warning(int ms) {
  if (millis() > led_status_warning_timer + ms) {
    set_led_status(!digitalRead(LED_STATUS));
    led_status_warning_timer = millis();
  }
}
