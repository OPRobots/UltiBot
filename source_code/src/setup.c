#include "setup.h"

/**
 * @brief Configura los relojes principales del robot
 *
 * SYSCLK a 168 MHz
 * GPIO: A, B, C
 * USART3
 * Timers: 1-PWM, 2-PID, 8-OneShot125
 * ADC
 * DWT
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

  //   // Entradas digitales configuracion
  //   gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO10 | GPIO11);
  //   gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO15);
  //   set_all_configs();

  //   if (get_config_track() == CONFIG_TRACK_LINEFOLLOWER) {
  //     // Entradas analógicas sensores de línea
  //     gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);
  //     gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO4 | GPIO5);
  //     gpio_mode_setup(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0 | GPIO1);
  //   } else {
  //     // Entradas analógicas sensores de línea
  //     gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);
  //     gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO4 | GPIO5);
  //     gpio_mode_setup(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0 | GPIO1);

  //     // Salidas digitales de conmutación de morros
  //     gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0 | GPIO1);
  //     activar_morro_corto();
  //   }

  //   // Entradas analógicas sensores de marcas
  //   gpio_mode_setup(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0 | GPIO1 | GPIO2 | GPIO3);

  //   // Entradas digitales Switch y botón de inicio
  //   gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);

  //   // Entradas Encoders
  //   gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4 | GPIO5 | GPIO6 | GPIO7);
  //   gpio_set_af(GPIOB, GPIO_AF2, GPIO4 | GPIO5 | GPIO6 | GPIO7);

  //   // Salida digital LED auxiliar
  //   gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

  //   // Salida PWM LEDS
  //   gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9 | GPIO10 | GPIO11);
  //   gpio_set_af(GPIOA, GPIO_AF1, GPIO8 | GPIO9 | GPIO10 | GPIO11);

  //   // Salida PWM Motores
  //   gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7 | GPIO8 | GPIO9);
  //   gpio_set_af(GPIOC, GPIO_AF3, GPIO6 | GPIO7 | GPIO8 | GPIO9);

  //   // USART3
  //   gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10 | GPIO11);
  //   gpio_set_af(GPIOB, GPIO_AF7, GPIO10 | GPIO11);
}

static void setup_rgb_timer(void) {
  timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // 84000000
  timer_set_prescaler(TIM4, 0);
  timer_enable_preload(TIM4);
  timer_set_repetition_counter(TIM4, 0);
  timer_continuous_mode(TIM4);
  timer_enable_irq(TIM4, TIM_DIER_UIE);

  timer_set_oc_mode(TIM4, TIM_OC4, TIM_OCM_PWM1);

  //   timer_set_period(TIM4, 1023);
  //   timer_set_oc_value(TIM4, TIM_OC4, 512);
  //   timer_enable_oc_output(TIM4, TIM_OC4);
  //   timer_enable_break_main_output(TIM4);
  //   timer_enable_counter(TIM4);

  calc_rgb_timings();
}

void tim4_isr(void) {
  if (timer_get_flag(TIM4, TIM_SR_UIF)) {
    timer_clear_flag(TIM4, TIM_SR_UIF);
    // gpio_toggle(GPIOC, GPIO13);
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