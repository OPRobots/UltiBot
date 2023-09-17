#include "motors.h"

void set_motors_speed(int8_t velI, int8_t velD) {
  send_command(CMD_MOTOR_SPEED_LEFT, velI);
  send_command(CMD_MOTOR_SPEED_RIGHT, velD);
}
