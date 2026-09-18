#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <compare>
#include "pico/stdlib.h"
#include <iostream>
#include <chrono>
#include <thread>

#define SW0 9
#define SW1 8
#define SW2 7
#define LED1 22
#define LED2 21
#define LED3 20

class GPIOPin {
public:
    GPIOPin(int pin, bool input = true, bool pullup = true, bool invert = false);

    GPIOPin(const GPIOPin &) = delete;

    ~GPIOPin();

    bool read(); // reads state of the GPIO pin
    void write(bool value);

    explicit operator bool(); // returns true if pin is usable and false if dormant
private:
    static uint32_t pins_in_use;
    // add others as needed
};

class SW_LED_PAIRING {
    public:
        SW_LED_PAIRING(int sw_pin,int led_pin){
            this->sw_pin = sw_pin;
            this->led_pin = led_pin;
        }
    void push_button() {
            
        }


    private:
    int sw_pin;
    int led_pin;
};


GPIOPin sw0(SW0, true, true, false);
GPIOPin sw1(SW1, true, true, false);
GPIOPin sw2(SW2, true, true, false);
GPIOPin led1(LED1, true, true, false);
GPIOPin led2(LED2, true, true, false);
GPIOPin led3(LED3, true, true, false);


GPIOPin write(bool value) {
    gpio_pin_set()
    sw0.set(true)
    return ;
}

int main() {


    return 0;
}
