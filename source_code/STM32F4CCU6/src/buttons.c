#include "buttons.h"
#include "delay.h"

/**
 * @brief Obtiene el estado del botón de inicio
 * 
 * @return bool
 */
bool get_start_btn() {
  bool state1 = (bool)gpio_get(GPIOA, GPIO15);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOA, GPIO15);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Arriba
 * 
 * @return bool
 */
bool get_menu_up_btn() {
  bool state1 = (bool)gpio_get(GPIOB, GPIO15);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOB, GPIO15);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Abajo
 * 
 * @return bool
 */
bool get_menu_down_btn() {
  bool state1 = (bool)gpio_get(GPIOB, GPIO13);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOB, GPIO13);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Modo
 * 
 * @return bool
 */
bool get_menu_mode_btn() {
  bool state1 = (bool)gpio_get(GPIOB, GPIO14);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOB, GPIO14);
  return !(state1 && state2);
}