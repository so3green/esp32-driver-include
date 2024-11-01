#include <Arduino.h>
#include <LoRa_Driver.h>

HardwareSerial Serial4(2);


#define X2 34
#define Y2 35
#define SW2 32
#define buttonR2 33
#define buttonR1 25
#define buttonR4 26
#define buttonR3 27
#define LED 14
#define ST 12
#define buttonL1 21
#define buttonL2 19
#define buttonL3 18
#define buttonL4 2
#define buttonL5 15
#define SW1 5
#define X1 4
#define Y1 0

volatile uint8_t LoRa_Driver::msg[7] = {0};
volatile uint8_t LoRa_Driver::data[14] = {0};


void LoRa_Driver::LoRa_init() noexcept{
  Serial.begin(SERIAL_SPEED);
  Serial4.begin(SERIAL1_SPEED);

  Serial.println("System Start");
  Serial.println("LoRa set up start");

  pinMode(buttonL1,INPUT);
  pinMode(buttonL2,INPUT);
  pinMode(buttonL3,INPUT);
  pinMode(buttonL4,INPUT);
  pinMode(buttonL5,INPUT);

  pinMode(buttonR1,INPUT);
  pinMode(buttonR2,INPUT);
  pinMode(buttonR3,INPUT);
  pinMode(buttonR4,INPUT);

  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  pinMode(X1,INPUT);
  pinMode(Y1,INPUT);
  pinMode(X2,INPUT);
  pinMode(Y2,INPUT);

  pinMode(LED,OUTPUT);
  LoRa_Driver::LED_off();
}

void LoRa_Driver::LoRa_send_data(uint8_t aim,u_int8_t setup,u_int8_t stop) noexcept{ //aim:送信先,setup:モータの作動,stop:非常停止(0:非常停止off,1:非常停止on)
  if(stop==1){
    LoRa_Driver::get_Data();
    LoRa_Driver::msg[0] = ((0b00000001<<7)+(aim <<4)+(0b00000011 <<2)+(setup <<1)+data[9]);
    LoRa_Driver::msg[1] = ((0b00000000+data[0] <<6)+(data[1] <<5)+(data[2] <<4)+(data[3] <<3)+(data[4] <<2)+(data[5] <<1)+data[6]);
    LoRa_Driver::msg[2] = ((0b00000000+data[7] <<6)+(data[8] <<5)+(data[9] <<4));
    LoRa_Driver::msg[3] = (data[10]/4);
    LoRa_Driver::msg[4] = (data[11]/4);
    LoRa_Driver::msg[5] = (data[12]/4);
    LoRa_Driver::msg[6] = (data[13]/4);
    Serial4.write(msg[0]);
    Serial4.write(msg[1]);
    Serial4.write(msg[2]);
    Serial4.write(msg[3]);
    Serial4.write(msg[4]);
    Serial4.write(msg[5]);
    Serial4.write(msg[6]);
    Serial.println(msg[0]);
    Serial.println(msg[1]);
    Serial.println(msg[2]);
    Serial.println(msg[3]);
    Serial.println(msg[4]);
    Serial.println(msg[5]);
    Serial.println(msg[6]);
    //Serial4.write(msg[5]);
    //Serial4.write(msg[6]);
    //Serial.println((msg[0]&0b10000000)>>7);
  }
}

void LoRa_Driver::LED_on() noexcept{
  digitalWrite(14,HIGH);
  Serial4.write(0b00101101);
  Serial4.write(0b00111101);
  Serial4.write(0b00101011);
  Serial4.write(0b00101100);
}

void LoRa_Driver::LED_off() noexcept{
  digitalWrite(14,LOW);
}

void LoRa_Driver::get_Data() noexcept{
  data[0]=digitalRead(21);  //buttonL1
  data[1]=digitalRead(19);  //buttonL2
  data[2]=digitalRead(18);  //buttonL3
  data[3]=digitalRead(2);   //buttonL4
  data[4]=digitalRead(15);  //buttonL5
  data[5]=digitalRead(25);  //buttonR1
  data[6]=digitalRead(33);  //buttonR2
  data[7]=digitalRead(27);  //buttonn3
  data[8]=digitalRead(26);  //buttonR4
  data[9]=digitalRead(12);  //SD
  data[10]=analogRead(X1);
  data[11]=analogRead(Y1);
  data[12]=analogRead(X2);
  data[13]=analogRead(Y2);
}
