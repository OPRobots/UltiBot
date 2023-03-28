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

  rcc_periph_clock_enable(RCC_TIM4);

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
  nvic_set_priority(NVIC_TIM4_IRQ, 16 * 2);
  //   nvic_set_priority(NVIC_TIM5_IRQ, 16 * 4);
  //   nvic_set_priority(NVIC_USART3_IRQ, 16 * 5);

  //   //   nvic_enable_irq(NVIC_TIM5_IRQ);
  //   nvic_enable_irq(NVIC_DMA2_STREAM0_IRQ);
  //   nvic_enable_irq(NVIC_TIM5_IRQ);
  nvic_enable_irq(NVIC_TIM4_IRQ);
  //   nvic_enable_irq(NVIC_USART3_IRQ);
}

static void setup_gpio(void) {
  // Builtin LED
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO13);

  // RGB LED
  gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);
  gpio_set_af(GPIOB, GPIO_AF2, GPIO9);
}

static void setup_rgb_timer(void) {
  timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_prescaler(TIM4, 0);
  timer_enable_preload(TIM4);
  timer_set_repetition_counter(TIM4, 0);
  timer_continuous_mode(TIM4);
  timer_enable_irq(TIM4, TIM_DIER_UIE);
  timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);

  init_rgb();
}

void tim4_isr(void) {
  if (timer_get_flag(TIM4, TIM_SR_UIF)) {
    timer_clear_flag(TIM4, TIM_SR_UIF);
    manage_rgb();
  }
}

void setup(void) {
  setup_clock();
  setup_gpio();
  setup_rgb_timer();
  setup_timer_priorities();

  setup_systick();
}