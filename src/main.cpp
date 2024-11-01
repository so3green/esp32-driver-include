#include <Arduino.h>
#include <LoRa_Driver.h>

void setup() {
  // put your setup code here, to run once:
  LoRa_Driver::LoRa_init();
}

void loop() {
  LoRa_Driver::get_Data();
  //LoRa_Driver::LED_on();
  LoRa_Driver::LoRa_send_data(2,1,1);
  delay(100);
}