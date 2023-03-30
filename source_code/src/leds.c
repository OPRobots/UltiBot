#include "leds.h"

#define timer_freq 84.0
#define T0H 0.5
#define T0L 1.2
#define T1H 2.0
#define T1L 1.3

static uint16_t low_CCR1;
static uint16_t high_CCR1;
static uint16_t low_ARR;
static uint16_t high_ARR;

static uint8_t LED_data[7 * 3];
static uint16_t pos;
static uint8_t mask = 0B10000000;
static uint8_t lastbit = 1;

void init_rgb(void) {
  clear_rgb();

  low_CCR1 = round(T0H / (1 / timer_freq));
  low_ARR = round((T0H + T0L) / (1 / timer_freq));
  high_CCR1 = round(T1H / (1 / timer_freq));
  high_ARR = round((T1H + T1L) / (1 / timer_freq));
}

void set_rgb(uint8_t index, int r, int g, int b) {
  LED_data[(index * 3) + 0] = g;
  LED_data[(index * 3) + 1] = r;
  LED_data[(index * 3) + 2] = b;
}

void clear_rgb(void) {
  for (uint8_t i = 0; i < sizeof(LED_data); i++) {
    LED_data[i] = 0;
  }
}

void update_rgb(void) {
  if (lastbit > 0) {
    if (LED_data[0] & 0B10000000) {
      timer_set_oc_value(TIM3, TIM_OC4, high_CCR1);
      timer_set_period(TIM3, high_ARR);
    } else {
      timer_set_oc_value(TIM3, TIM_OC4, low_CCR1);
      timer_set_period(TIM3, low_ARR);
    }

    pos = 0;
    lastbit = 0;
    mask = 0B01000000;

    timer_enable_oc_output(TIM3, TIM_OC4);
    timer_enable_break_main_output(TIM3);
    timer_enable_counter(TIM3);
  }
}

void manage_rgb(void) {
  if (pos < sizeof(LED_data)) {
    if (LED_data[pos] & mask) {
      timer_set_oc_value(TIM3, TIM_OC4, high_CCR1);
      timer_set_period(TIM3, high_ARR);
    } else {
      timer_set_oc_value(TIM3, TIM_OC4, low_CCR1);
      timer_set_period(TIM3, low_ARR);
    }
    if (mask == 1) {
      mask = 0B10000000;
      pos++;
    } else {
      mask = mask >> 1;
    }
  } else {
    if (lastbit) {
      timer_disable_oc_output(TIM3, TIM_OC4);
      timer_disable_break_main_output(TIM3);
      timer_disable_counter(TIM3);
    }
    lastbit = 1;
  }
}
