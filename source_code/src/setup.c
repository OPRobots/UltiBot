#include "setup.h"

/**
 * @brief Configura los relojes principales del robot
 *
 * SYSCLK a 84 MHz
 * GPIO: A, B, C
 * USART3
 * Timers: 1-PWM, 4-ADDR_LED
 *
 */
static void setup_clock(void) {
  rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  
  rcc_periph_clock_enable(RCC_USART1);

  rcc_periph_clock_enable(RCC_TIM4);
  rcc_periph_clock_enable(RCC_TIM3);

  dwt_enable_cycle_counter();
}

/**
 * @brief Configura el SysTick para 1ms
 *
 */
static void setup_systick(void) {
  systick_set_frequency(SYSTICK_FREQUENCY_HZ, SYSCLK_FREQUENCY_HZ);
  systick_counter_enable();
  systick_interrupt_enable();
}

static void setup_timer_priorities(void) {
  nvic_set_priority(NVIC_SYSTICK_IRQ, 16 * 1);
  //   nvic_set_priority(NVIC_DMA2_STREAM0_IRQ, 16 * 2);
  nvic_set_priority(NVIC_TIM3_IRQ, 16 * 2);
  //   nvic_set_priority(NVIC_TIM5_IRQ, 16 * 4);
    nvic_set_priority(NVIC_USART1_IRQ, 16 * 3);

  //   //   nvic_enable_irq(NVIC_TIM5_IRQ);
  //   nvic_enable_irq(NVIC_DMA2_STREAM0_IRQ);
  //   nvic_enable_irq(NVIC_TIM5_IRQ);
  nvic_enable_irq(NVIC_TIM3_IRQ);
    nvic_enable_irq(NVIC_USART1_IRQ);
}

static void setup_gpio(void) {
  // Builtin LED
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO13);
  // Builtin BTN
  gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO0);

  // RGB LED
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO1);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO1);

  // Salida PWM para los motores
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7 | GPIO8 | GPIO9);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO6 | GPIO7 | GPIO8 | GPIO9);

    // USART1
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);
}

static void setup_rgb_timer(void) {
  timer_set_mode(TIM3, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_prescaler(TIM3, 0);
  timer_enable_preload(TIM3);
  timer_set_repetition_counter(TIM3, 0);
  timer_continuous_mode(TIM3);
  timer_enable_irq(TIM3, TIM_DIER_UIE);
  timer_set_oc_mode(TIM3, TIM_OC4, TIM_OCM_PWM1);

  init_rgb();
}

void tim3_isr(void) {
  if (timer_get_flag(TIM3, TIM_SR_UIF)) {
    timer_clear_flag(TIM3, TIM_SR_UIF);
    manage_rgb();
  }
}

static void setup_motors_pwm(void) {
  timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // timer_set_prescaler(TIM4, 2); // 27khz🔥
  timer_set_prescaler(TIM4, 80); // 1khz
  timer_set_repetition_counter(TIM4, 0);
  timer_enable_preload(TIM4);
  timer_continuous_mode(TIM4);
  timer_set_period(TIM4, MOTORES_MAX_PWM);

  timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);
  timer_set_oc_mode(TIM4, TIM_OC2, TIM_OCM_PWM1);
  timer_set_oc_mode(TIM4, TIM_OC3, TIM_OCM_PWM1);
  timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);
  timer_set_oc_value(TIM4, TIM_OC1, MOTORES_MAX_PWM);
  timer_set_oc_value(TIM4, TIM_OC2, MOTORES_MAX_PWM - MOTORES_MAX_PWM*0.25);
  timer_set_oc_value(TIM4, TIM_OC3, MOTORES_MAX_PWM);
  timer_set_oc_value(TIM4, TIM_OC4, MOTORES_MAX_PWM - MOTORES_MAX_PWM*0.25);
  timer_enable_oc_output(TIM4, TIM_OC1);
  timer_enable_oc_output(TIM4, TIM_OC2);
  timer_enable_oc_output(TIM4, TIM_OC3);
  timer_enable_oc_output(TIM4, TIM_OC4);

  timer_enable_break_main_output(TIM4);

  timer_enable_counter(TIM4);
}


static void setup_usart(void) {
  usart_set_baudrate(USART1, 115200);
  usart_set_databits(USART1, 8);
  usart_set_stopbits(USART1, USART_STOPBITS_1);
  usart_set_parity(USART1, USART_PARITY_NONE);
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
  usart_set_mode(USART1, USART_MODE_TX_RX);
  // USART_CR1(USART1) |= USART_CR1_RXNEIE;
  // usart_enable_tx_interrupt(USART1);
  usart_enable(USART1);
}


void setup(void) {
  setup_clock();
  setup_gpio();
  setup_rgb_timer();
  setup_motors_pwm();
  setup_usart();

  setup_timer_priorities();
  setup_systick();
}