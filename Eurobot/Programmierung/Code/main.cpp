#include <unistd.h>
#include <string>
#include <sys/types.h>  
#include <time.h>
#include <iostream>
#include "gpio.h"

#include <chrono>
#include <thread>

#if 1


GPIO IN1(GPIO_67);
GPIO IN2(GPIO_68);
GPIO IN3(GPIO_44);
GPIO IN4(GPIO_26);

int main(void)
{
    IN1.gpioSetDirection(PIN_OUT);
    IN2.gpioSetDirection(PIN_OUT);
    IN3.gpioSetDirection(PIN_OUT);
    IN4.gpioSetDirection(PIN_OUT);

    while(1)
    {
        for(int i = 1000;i<16000; i+=100)
        {
        IN1.gpioSetValue(LOW);
        IN2.gpioSetValue(LOW);
        IN3.gpioSetValue(LOW);
        IN4.gpioSetValue(HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(LOW);
        IN2.gpioSetValue(LOW);
        IN3.gpioSetValue(HIGH);
        IN4.gpioSetValue(HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(LOW);
        IN2.gpioSetValue(LOW);
        IN3.gpioSetValue(HIGH);
        IN4.gpioSetValue(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(LOW);
        IN2.gpioSetValue(HIGH);
        IN3.gpioSetValue(HIGH);
        IN4.gpioSetValue(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(LOW);
        IN2.gpioSetValue(HIGH);
        IN3.gpioSetValue(LOW);
        IN4.gpioSetValue(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(HIGH);
        IN2.gpioSetValue(HIGH);
        IN3.gpioSetValue(LOW);
        IN4.gpioSetValue(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(HIGH);
        IN2.gpioSetValue(LOW);
        IN3.gpioSetValue(LOW);
        IN4.gpioSetValue(LOW);
        std::this_thread::sleep_for(std::chrono::microseconds(i));
        IN1.gpioSetValue(HIGH);
        IN2.gpioSetValue(LOW);
        IN3.gpioSetValue(LOW);
        IN4.gpioSetValue(HIGH);
        std::this_thread::sleep_for(std::chrono::microseconds(i));

    }
        }
        




   return 0;    
}
#endif

