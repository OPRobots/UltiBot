#include "config.h"
#include "delay.h"
#include "leds.h"
#include "setup.h"

void sys_tick_handler(void) {
  clock_tick();
  update_rgb();
}

int main(void) {
  setup();

  while (1) {
    if(gpio_get(GPIOA, GPIO0)){
      gpio_set(GPIOC, GPIO13);
    }else{
      gpio_clear(GPIOC, GPIO13);
    }
    // for (int i = 0; i < 7; i++) {
    //   set_rgb(i, 25, 0, 0);
    //   delay(250);
    //   set_rgb(i, 0, 25, 0);
    //   delay(250);
    //   set_rgb(i, 0, 0, 25);
    //   delay(250);
    // }
    // clear_rgb();
    // delay(500);
  }
  return 0;
}