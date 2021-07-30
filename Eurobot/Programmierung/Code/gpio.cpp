#include "stdafx.h"
#include "gpio.h"


GPIO::GPIO(){}

/****f* gpio.h/gpioSetPin()
  *  NAME
  *    gpioSetPin() -- generiert die Ordnerpfade, um den entsprechenden GPIO - Pin einstellen zu können
  *  INPUTS
  *     _m_pin
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void GPIO::gpioSetPin(GPIOPin _m_pin)
{
  m_pin = _m_pin;
  valuePath = "/sys/class/gpio/gpio" + std::to_string(m_pin) + "/value";
  directionPath = "/sys/class/gpio/gpio" + std::to_string(m_pin) + "/direction";
  edgePath = "/sys/class/gpio/gpio" + std::to_string(m_pin) + "/edge";
  activelowPath = "/sys/class/gpio/gpio" + std::to_string(m_pin) + "/activelow";
}

/****f* gpio.h/gpioGetPin()
  *  NAME
  *    gpioGetPin() -- gibt den gesetzten GPIOPin zurück; GPIO_IDLE -> kein Pin gesetzt
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     GPIOPin m_pin    
  ******
  * 
*/
GPIOPin GPIO::gpioGetPin()
{
  return m_pin;
}


/****f* gpio.h/gpioSetDirection()
  *  NAME
  *    gpioSetDirection() -- setzen auf Input oder Output Pin
  *  INPUTS
  *    PinDirection _dircetion; PIN_IN oder PIN_OUT
  *  RETURN VALUE
  *        
  ******
  * 
*/
bool GPIO::gpioSetDirection(PinDirection _direction)
{
    std::fstream fs(directionPath);
    (_direction == PIN_OUT) ? (fs << "out") : (fs<<"in");
    fs.close();
    return 0;
}

/****f* gpio.h/gpioGetDirection()
  *  NAME
  *    gpioGetDirection() -- Rückgabe direction
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     bool
  *  IDEAS
  *    
  ******
  * 
*/
bool GPIO::gpioGetDirection()
{
    std::fstream fs(directionPath);
    std::string value;
    fs >> value;
    fs.close();

    return (value == "in") ? PIN_IN : PIN_OUT;
}

/****f* gpio.h/gpioSetValue()
  *  NAME
  *    gpioSetValue() -- Sets the attribute value of the class GPIO to the input value
  *  INPUTS
  *     _value - Value which overrides the attribute value
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
bool GPIO::gpioSetValue(PinValue _value)
{
    std::fstream fs(valuePath);
    (_value == LOW) ? (fs << LOW) : (fs<<HIGH);
    fs.close();
    return 0;
}

/****f* gpio.h/gpioGetValue()
  *  NAME
  *    gpioGetValue()  
  ******
   * 
  */
bool GPIO::gpioGetValue()
{
    std::fstream fs(valuePath);
    std::string value;
    fs >> value;
    fs.close();
    return (value == "1") ? HIGH : LOW;
}

/****f* gpio.h/gpioSetEdge()
  *  NAME
  *    gpioSetEdge() -- Sets the attribute edge of the class GPIO to the input value
  *  INPUTS
  *     _edge - Value which overrides the attribute edge
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
int GPIO::gpioSetEdge(char _edge)
{
    std::fstream fs(edgePath);
    fs << _edge;
    fs.close();
    return 0;
}

/****f* gpio.h/gpioActiveLow()
  *  NAME
  *    gpioActiveLow() -- Sets the attribute activeLows of the class GPIO to the input value
  *  INPUTS
  *     _activeLows - Value which overrides the attribute activeLows
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
int GPIO::gpioActiveLow(unsigned int _activeLow)
{
    std::fstream fs(activelowPath);
    fs << _activeLow;
    fs.close();
    return 0;
}

