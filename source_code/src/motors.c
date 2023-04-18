#include "motors.h"

void set_motors_speed(float velI, float velD) {
  velI = constrain(velI, -100, 100);
  velD = constrain(velD, -100, 100);

  if (velI >= 0) {
    timer_set_oc_value(TIM4, TIM_OC3, MOTORES_MAX_PWM);
    timer_set_oc_value(TIM4, TIM_OC4, MOTORES_MAX_PWM - MOTORES_MAX_PWM * velD / 100);
  } else {
    timer_set_oc_value(TIM4, TIM_OC3, MOTORES_MAX_PWM - MOTORES_MAX_PWM * abs(velD) / 100));
    timer_set_oc_value(TIM4, TIM_OC4, MOTORES_MAX_PWM);
  }

  if (velD >= 0) {
    timer_set_oc_value(TIM4, TIM_OC1, MOTORES_MAX_PWM);
    timer_set_oc_value(TIM4, TIM_OC2, MOTORES_MAX_PWM - MOTORES_MAX_PWM * velI / 100);
  } else {
    timer_set_oc_value(TIM4, TIM_OC1, MOTORES_MAX_PWM - MOTORES_MAX_PWM * abs(velI) / 100);
    timer_set_oc_value(TIM4, TIM_OC2, MOTORES_MAX_PWM);
  }
}
