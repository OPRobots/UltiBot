#include "buttons.h"

/**
 * @brief Obtiene el estado del botón de inicio
 * 
 * @return bool
 */
bool get_start_btn() {
  bool state1 = (bool)digitalRead(BTN_START);
  delay(25);
  bool state2 = (bool)digitalRead(BTN_START);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Arriba
 * 
 * @return bool
 */
bool get_menu_up_btn() {
  bool state1 = (bool)digitalRead(BTN_MENU_UP);
  delay(25);
  bool state2 = (bool)digitalRead(BTN_MENU_UP);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Abajo
 * 
 * @return bool
 */
bool get_menu_down_btn() {
  bool state1 = (bool)digitalRead(BTN_MENU_DO);
  delay(25);
  bool state2 = (bool)digitalRead(BTN_MENU_DO);
  return !(state1 && state2);
}

/**
 * @brief Obtiene el estado del botón de Menú Modo
 * 
 * @return bool
 */
bool get_menu_mode_btn() {
  bool state1 = (bool)digitalRead(BTN_MENU_MO);
  delay(25);
  bool state2 = (bool)digitalRead(BTN_MENU_MO);
  return !(state1 && state2);
}