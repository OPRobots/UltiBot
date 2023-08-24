#ifndef DEBUG_H
#define DEBUG_H

#include <commons.h>
#include <sensors.h>

void debugIO(void);
void debug_sensors_raw(void);
void debug_sensors_calibrated(void);
void debug_sensors_position(void);

#endif