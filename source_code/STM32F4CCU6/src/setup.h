#ifndef __SETUP_H
#define __SETUP_H

#include <libopencm3/cm3/dwt.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>

#include "config.h"
#include "leds.h"
#include "sensors.h"
#include "usart.h"

void setup(void);
void setup_spi_high_speed(void);
void setup_spi_low_speed(void);

#endif