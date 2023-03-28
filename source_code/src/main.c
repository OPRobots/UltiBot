#include "config.h"
#include "delay.h"
#include "leds.h"
#include "setup.h"

void sys_tick_handler(void) {
  clock_tick();
  show_rgb();
}

int main(void) {
  setup();

  // gpio_set(GPIOC, GPIO13);

  while (1) {
    set_rgb(0, 25, 0, 0);
    delay(1000);
    set_rgb(0, 0, 25, 0);
    delay(1000);
    set_rgb(0, 0, 0, 25);
    delay(1000);
    // set_rgb(0, 0, 0, 0);
    // set_rgb(1, 25, 0, 0);
    // delay(1000);
    // set_rgb(1, 0, 25, 0);
    // delay(1000);
    // set_rgb(1, 0, 0, 25);
    // delay(1000);
    // set_rgb(1, 0, 0, 0);
    //   gpio_toggle(GPIOC, GPIO13);
  }
  return 0;
}