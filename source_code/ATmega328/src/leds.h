#ifndef LEDS_H
#define LEDS_H

#include "commons.h"

void set_leds(bool state);
void set_leds_fatal_error(void);

void set_led_left(bool state);
void set_led_center(bool state);
void set_led_right(bool state);

void set_led_left_warning(unsigned int ms);
void set_led_center_warning(unsigned int ms);
void set_led_right_warning(unsigned int ms);

void set_led_status(bool state);
void set_led_status_warning(int ms);

#endif