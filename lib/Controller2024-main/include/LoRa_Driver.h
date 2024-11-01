#include <Arduino.h>
constexpr int SERIAL_SPEED = 115200; //Serialの通信速度
constexpr int SERIAL1_SPEED = 115200; //Serial1の通信速度。主にLoRaとの通信に使用。


namespace LoRa_Driver{
    extern volatile uint8_t msg[7];
    extern volatile uint8_t data[14];
    void LoRa_init() noexcept;
    void LoRa_send_data(uint8_t aim,u_int8_t setup,u_int8_t stop) noexcept; //aim:送信先,setup:モータの作動,stop:非常停止(0:非常停止off,1:非常停止on)
    void LED_on() noexcept;
    void LED_off() noexcept;
    void get_Data() noexcept;
}