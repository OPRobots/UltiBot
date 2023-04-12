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

static uint32_t rainbow_rgb_timer = 0;
static uint32_t rainbow_rgb[3] = {LEDS_MAX_PWM, 0, 0};
static uint8_t rainbow_color_desc = 0;
static uint8_t rainbow_color_asc = 1;

static uint32_t loading_rgb_timer = 0;
static uint8_t loading_rgb_index = 0;
static uint8_t loading_rgb_leds[] = { LED_FRONT, LED_FRONT_RIGHT, LED_BACK_RIGHT, LED_BACK, LED_BACK_LEFT, LED_FRONT_LEFT };

void init_rgb(void) {
  clear_rgb();

  low_CCR1 = round(T0H / (1 / timer_freq));
  low_ARR = round((T0H + T0L) / (1 / timer_freq));
  high_CCR1 = round(T1H / (1 / timer_freq));
  high_ARR = round((T1H + T1L) / (1 / timer_freq));
}

void set_rgb(enum LEDS led, uint8_t r, uint8_t g, uint8_t b) {
  LED_data[(led * 3) + 0] = g;
  LED_data[(led * 3) + 1] = r;
  LED_data[(led * 3) + 2] = b;
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

static void update_rainbow_rgb(void) {
  rainbow_rgb[rainbow_color_desc] -= 10;
  rainbow_rgb[rainbow_color_asc] += 10;
  if (rainbow_rgb[rainbow_color_desc] <= 0 || rainbow_rgb[rainbow_color_asc] >= LEDS_MAX_PWM) {
    rainbow_rgb[rainbow_color_desc] = 0;
    rainbow_rgb[rainbow_color_asc] = LEDS_MAX_PWM;
    rainbow_color_desc++;
    if (rainbow_color_desc > 2) {
      rainbow_color_desc = 0;
    }
    rainbow_color_asc = rainbow_color_desc == 2 ? 0 : rainbow_color_desc + 1;
  }
}

void set_rainbow_rgb(enum LEDS led) {
  if (get_clock_ticks() > rainbow_rgb_timer + 10) {
    rainbow_rgb_timer = get_clock_ticks();
    update_rainbow_rgb();
    set_rgb(led, rainbow_rgb[0], rainbow_rgb[1], rainbow_rgb[2]);
  }
}

void set_loading_rgb(void) {
  if ((get_clock_ticks() - loading_rgb_timer + 50) > 500) {
    loading_rgb_index = 0;
  }
  if (get_clock_ticks() > loading_rgb_timer + 50) {
    loading_rgb_timer = get_clock_ticks();
    update_rainbow_rgb();
    set_rgb(loading_rgb_leds[loading_rgb_index], rainbow_rgb[0], rainbow_rgb[1], rainbow_rgb[2]);
    loading_rgb_index++;
    if (loading_rgb_index > sizeof(loading_rgb_leds) / sizeof(loading_rgb_leds[0])) {
      loading_rgb_index = 0;
    }
  }
}