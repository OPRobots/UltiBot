#include "buttons.h"
#include "delay.h"

/**
 * @brief Obtiene el estado del botón de inicio
 * 
 * @return bool
 */
bool get_start_btn() {
  bool state1 = (bool)gpio_get(GPIOB, GPIO8);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOB, GPIO8);
  return state1 && state2;
}

/**
 * @brief Obtiene el estado del botón de Menú Modo
 * 
 * @return bool
 */
bool get_menu_mode_btn() {
  bool state1 = (bool)gpio_get(GPIOB, GPIO9);
  delay(50);
  bool state2 = (bool)gpio_get(GPIOB, GPIO9);
  return state1 && state2;
}