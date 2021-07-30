#ifndef GPIO_H
#define GPIO_H
#include <iostream>
#include <fstream>
#include <string>
#define MAX_BUF        64

/****** gpio.h/PinValue
 *  NAME
 *    PinValue -- Alternatives for 0 and 1
******
*/
enum PinValue {
    LOW  = 0,
    HIGH = 1,
};

/****** gpio.h/PinDirection
 *  NAME
 *    PinDirection -- Alternatives for "in" and "out"
******
*/
enum PinDirection {
    PIN_IN  = 0,
    PIN_OUT = 1,
};

/****** gpio.h/GPIOPin
 *  NAME
 *    GPIOPin -- This is an enum to match the names to the gpio pins of the beagle bone black.
 *  NOTE
 *    The BeagleBone Black got two pin sockets P9 and P8
 *    In the enum definition the GPIO pins are sorted by their socket
******
*/
enum GPIOPin {
    // TODO Naming? GPIO_INVALID?
    GPIO_IDLE = 0,
    //P9
    GPIO_48 = 48,
    GPIO_49 = 49,
    GPIO_117 = 117,
    GPIO_115 = 115,
    GPIO_20 = 20,
    GPIO_60 = 60,
    GPIO_112 = 112,

    //P8
    GPIO_66 = 66,
    GPIO_69 = 69,
    GPIO_45 = 45,
    GPIO_47 = 47,
    GPIO_27 = 27,
    GPIO_67 = 67,
    GPIO_68 = 68,
    GPIO_44 = 44,
    GPIO_26 = 26,
    GPIO_46 = 46,
    GPIO_65 = 65,
    GPIO_61 = 61,
};

 /****c* gpio.h/GPIO
  *  NAME
  *    GPIO -- This class provides operations to controll the gpio pins on the beagelbone black.
  *  DESCRIPTION
  *    The class GPIO is an interface between the developed software and the beaglebone black.
  *    It provides operations to controll the gpio pins of the beaglebone black. 
  *    Furthermore it provides attributes with the values of last known status of the gpio.
  *  METHODS
  *    gpioExport()
  *    gpioUnexport()
  *    gpioSetDirection()
  *    gpioGetDirection()
  *    gpioSetValue()
  *    gpioGetValue()
  *    gpioSetEdge()
  *    gpioActiveLow()
  *  ATTRIBUTES
  *     GPIOPin          - gültige Werde sind in GPIOPin aufgelistet
  *     directionPath    
  *     valuePath        
  *     edgePath         
  *     activelowPath     
  *  NOTES
  *     edge und activelow wurden bisher nicht benötigt. Werden diese Optionen dennoch irgendwann mal benötigt, müssen, zum auslesen, passende Methoden geschrieben werden
  ******
  * 
  */ 
class GPIO
{



public:
    GPIO();
    

   
    GPIOPin m_pin;



    void gpioSetPin(GPIOPin _m_pin);
    GPIOPin gpioGetPin();
    bool gpioSetDirection(PinDirection _direction);
    bool gpioGetDirection();
    bool gpioSetValue(PinValue _value);
    bool gpioGetValue();
    int gpioSetEdge(char _edge);
    int gpioActiveLow(unsigned int _activeLow);

private:

    std::string directionPath;
    std::string valuePath;
    std::string edgePath;
    std::string activelowPath;

    
};

#endif // GPIO_H
