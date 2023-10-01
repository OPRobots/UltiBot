#include "motors.h"

void set_motors_speed(int16_t velD, int16_t velI) {
  if (velI > 80) {
    velI = 80;
  } else if (velI < -80) {
    velI = -80;
  }
  if (velD > 80) {
    velD = 80;
  } else if (velD < -80) {
    velD = -80;
  }

  // printf("%d | %d\n", velD, velI);
  send_command(CMD_MOTOR_SPEED_LEFT, velI);
  send_command(CMD_MOTOR_SPEED_RIGHT, velD);
}
