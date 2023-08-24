#include "motors.h"

/**
 * @brief Establece la velocidad de los motores en base al porcentaje de la
 * velocidad máxima (0-100)
 *
 * @param velI
 * @param velD
 */
void set_speed(int velI, int velD) {
  if (velD > 100) {
    velD = 100;
  } else if (velD < -100) {
    velD = -100;
  }
  if (velI > 100) {
    velI = 100;
  } else if (velI < -100) {
    velI = -100;
  }

  if (velI >= 0) {
    analogWrite(MOTOR_DER_A, MAX_PWM - MAX_PWM * velI / 100);
    analogWrite(MOTOR_DER_B, MAX_PWM);
  } else {
    analogWrite(MOTOR_DER_A, MAX_PWM);
    analogWrite(MOTOR_DER_B, MAX_PWM - MAX_PWM * abs(velI) / 100);
  }

  if (velD >= 0) {
    analogWrite(MOTOR_IZQ_A, MAX_PWM - MAX_PWM * velD / 100);
    analogWrite(MOTOR_IZQ_B, MAX_PWM);
  } else {
    analogWrite(MOTOR_IZQ_A, MAX_PWM);
    analogWrite(MOTOR_IZQ_B, MAX_PWM - MAX_PWM * abs(velD) / 100);
  }
}