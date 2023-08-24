#include "debug.h"

void debug_sensors_raw() {
  for (int sensor = 0; sensor < 6; sensor++) {
    Serial.print(get_sensor_raw((enum SENSORS)sensor));
    Serial.print("\t");
  }
  Serial.println();
  delay(50);
}

void debug_sensors_calibrated() {
  for (int sensor = 0; sensor < 6; sensor++) {
    Serial.print(get_sensor_calibrated((enum SENSORS)sensor));
    // Serial.print("(");
    // Serial.print(get_sensor_raw((enum SENSORS)sensor));
    // Serial.print(")");
    Serial.print("\t");
  }
  Serial.println();
  delay(50);
}

void debug_sensors_position(){
  Serial.println(get_sensor_position());
  delay(50);
}

void debugIO() {
  digitalWrite(LED_DER, !digitalRead(BTN_MENU_UP));
  digitalWrite(LED_CEN, !digitalRead(BTN_MENU_DO));
  digitalWrite(LED_IZQ, !digitalRead(BTN_MENU_MO) || !digitalRead(BTN_START));

  Serial.print(analogRead(SENSOR_LAT_IZQ));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_ANG_IZQ));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_FRO_IZQ));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_LIN_IZQ));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_LIN_DER));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_FRO_DER));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_ANG_DER));
  Serial.print("\t");
  Serial.print(analogRead(SENSOR_LAT_DER));
  Serial.print("\n");

  delay(50);
}