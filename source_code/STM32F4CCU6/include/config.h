#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdio.h>

#define SYSCLK_FREQUENCY_HZ 84000000
#define SYSTICK_FREQUENCY_HZ 1000
#define MICROSECONDS_PER_SECOND 1000000
#define PI 3.1415

#define MS_CALIBRACION_LINEA 2000
#define LECTURA_MAXIMO_SENSORES_LINEA 4096
#define LECTURA_MINIMO_SENSORES_LINEA 0

#define MOTORES_MAX_PWM 1023
#define LEDS_MAX_PWM 100//255

#define MILLIS_INICIO 5000


uint16_t get_start_millis(void);

#endif