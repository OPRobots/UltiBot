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
    for(int i = 0; i < 7; i++) {
      set_rgb(i, 25, 0, 0);
      delay(250);
      set_rgb(i, 0, 25, 0);
      delay(250);
      set_rgb(i, 0, 0, 25);
      delay(250);
    }
    clear_rgb();
    delay(500);
    //   gpio_toggle(GPIOC, GPIO13);
  }
  return 0;
}