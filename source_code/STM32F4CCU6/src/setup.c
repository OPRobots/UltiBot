#include "setup.h"

static enum RC5_TRIGGER rc5_trigger = RC5_TRIGGER_FALLING;

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

  rcc_periph_clock_enable(RCC_SYSCFG);

  rcc_periph_clock_enable(RCC_USART1);
  rcc_periph_clock_enable(RCC_USART6);

  rcc_periph_clock_enable(RCC_ADC1);

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
  nvic_set_priority(NVIC_TIM3_IRQ, 16 * 2);
  nvic_set_priority(NVIC_DMA2_STREAM0_IRQ, 16 * 3);
  //   nvic_set_priority(NVIC_TIM5_IRQ, 16 * 4);
  nvic_set_priority(NVIC_USART6_IRQ, 16 * 4);
  nvic_set_priority(NVIC_USART1_IRQ, 16 * 5);

  //   //   nvic_enable_irq(NVIC_TIM5_IRQ);
  nvic_enable_irq(NVIC_DMA2_STREAM0_IRQ);
  //   nvic_enable_irq(NVIC_TIM5_IRQ);
  nvic_enable_irq(NVIC_TIM3_IRQ);
  nvic_enable_irq(NVIC_USART1_IRQ);
  nvic_enable_irq(NVIC_USART6_IRQ);
}

static void setup_gpio(void) {
  // LEDs
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO8);
  gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO1 | GPIO2 | GPIO10);
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP, GPIO13 | GPIO14 | GPIO15);

  // Botón de inicio y modo de menú
  gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO8 | GPIO9);

  // Entradas analógicas sensores
  gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7);

  // USART1
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9 | GPIO10);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);

  // USART6
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11 | GPIO12);
  gpio_set_af(GPIOA, GPIO_AF8, GPIO11 | GPIO12);

  // Start Module
  gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO3);
  // gpio_set_af(GPIOB, GPIO_AF15, GPIO3);

  nvic_enable_irq(NVIC_EXTI3_IRQ);
  exti_select_source(EXTI3, GPIOB);
  rc5_trigger = RC5_TRIGGER_FALLING;
  exti_set_trigger(EXTI3, EXTI_TRIGGER_FALLING);
  exti_enable_request(EXTI3);
}

void exti3_isr(void) {
  exti_reset_request(EXTI3);
  rc5_register(rc5_trigger);
  switch (rc5_trigger) {
    case RC5_TRIGGER_FALLING:
      rc5_trigger = RC5_TRIGGER_RISING;
      exti_set_trigger(EXTI3, EXTI_TRIGGER_RISING);
      break;
    case RC5_TRIGGER_RISING:
      rc5_trigger = RC5_TRIGGER_FALLING;
      exti_set_trigger(EXTI3, EXTI_TRIGGER_FALLING);
      break;
  }
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

static void setup_usart_foc(void) {
  usart_set_baudrate(USART6, 115200);
  usart_set_databits(USART6, 8);
  usart_set_stopbits(USART6, USART_STOPBITS_1);
  usart_set_parity(USART6, USART_PARITY_NONE);
  usart_set_flow_control(USART6, USART_FLOWCONTROL_NONE);
  usart_set_mode(USART6, USART_MODE_TX_RX);
  USART_CR1(USART6) |= USART_CR1_RXNEIE;
  // usart_enable_rx_interrupt(USART6);
  usart_enable(USART6);
}

void usart6_isr(void) {
  static uint8_t i = 0;
  static char command[8];

  /* Check if we were called because of RXNE. */
  if (((USART_CR1(USART6) & USART_CR1_RXNEIE) != 0) &&
      ((USART_SR(USART6) & USART_SR_RXNE) != 0)) {

    uint8_t data = usart_recv(USART6);
    if (data != '\n') {
      command[i++] = data;
    } else {
      manage_command(command[0], atoi(&command[1]));
      for (uint8_t p = 0; p < i; p++) {
        command[p] = '\0';
      }
      i = 0;
    }
  }
}

static void setup_adc1(void) {
  adc_power_off(ADC1);
  adc_disable_external_trigger_regular(ADC1);
  adc_set_resolution(ADC1, ADC_CR1_RES_12BIT);
  adc_set_right_aligned(ADC1);
  // adc_set_clk_prescale(ADC_CCR_ADCPRE_BY2);
  adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_15CYC);
  adc_enable_scan_mode(ADC1);

  adc_set_regular_sequence(ADC1, get_sensors_num(), get_sensors());
  adc_set_continuous_conversion_mode(ADC1);
  adc_enable_eoc_interrupt(ADC1);

  adc_power_on(ADC1);
  int i;
  for (i = 0; i < 800000; i++) {
    /* Wait a bit. */
    __asm__("nop");
  }

  adc_start_conversion_regular(ADC1);
}

static void setup_dma_adc1(void) {
  rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
  rcc_peripheral_enable_clock(&RCC_AHB1ENR, RCC_AHB1ENR_DMA2EN);
  dma_stream_reset(DMA2, DMA_STREAM0);

  dma_set_peripheral_address(DMA2, DMA_STREAM0, (uint32_t)&ADC_DR(ADC1));
  dma_set_memory_address(DMA2, DMA_STREAM0, (uint32_t)get_sensors_raw());
  dma_enable_memory_increment_mode(DMA2, DMA_STREAM0);
  dma_set_peripheral_size(DMA2, DMA_STREAM0, DMA_SxCR_PSIZE_16BIT);
  dma_set_memory_size(DMA2, DMA_STREAM0, DMA_SxCR_MSIZE_16BIT);
  dma_set_priority(DMA2, DMA_STREAM0, DMA_SxCR_PL_LOW);

  dma_enable_transfer_complete_interrupt(DMA2, DMA_STREAM0);
  // dma_enable_half_transfer_interrupt(DMA2, DMA_STREAM0);
  dma_set_number_of_data(DMA2, DMA_STREAM0, get_sensors_num());
  dma_enable_circular_mode(DMA2, DMA_STREAM0);
  dma_set_transfer_mode(DMA2, DMA_STREAM0, DMA_SxCR_DIR_PERIPHERAL_TO_MEM);
  dma_channel_select(DMA2, DMA_STREAM0, DMA_SxCR_CHSEL_0);

  dma_enable_stream(DMA2, DMA_STREAM0);
  adc_enable_dma(ADC1);
  adc_set_dma_continue(ADC1);
}

void dma2_stream0_isr(void) {
  if (dma_get_interrupt_flag(DMA2, DMA_STREAM0, DMA_TCIF)) {
    dma_clear_interrupt_flags(DMA2, DMA_STREAM0, DMA_TCIF);
  }
}

void setup(void) {
  setup_clock();
  setup_gpio();
  setup_usart();
  setup_usart_foc();
  setup_dma_adc1();
  setup_adc1();

  setup_timer_priorities();
  setup_systick();
}
