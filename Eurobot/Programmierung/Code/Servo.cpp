#include "Servo.h"




Servo::Servo(){}

Servo::~Servo(){}

/****f* Servo.h/setMinDutyCycle()
  *  NAME
  *    setMinDutyCycle() -- setzen der Pulsweite für Winkelstellung 0°
  *  INPUTS
  *     _minDutyCycle - Pulsweite für Winkelstellung 0°
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/      
void Servo::setMinDutyCycle(uint32_t _minDutyCycle)
{
    minDutyCycle = _minDutyCycle;
}

/****f* Servo.h/getMinDutyCycle()
  *  NAME
  *    getMinDutyCycle() -- Rückgabe der Pulsweite für Winkelstellung 0°
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint32_t 
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
*/
uint32_t Servo::getMinDutyCycle()
{
    return minDutyCycle;
}

/****f* Servo.h/setMaxDutyCycle()
  *  NAME
  *    setMaxDutyCycle() -- setzen der Pulsweite für Winkelstellung 180°
  *  INPUTS
  *     uint32_t - Pulsweite für Winkelstellung 180°
  *  RETURN VALUE
  *     NONE
  * 
  ******
  * 
*/       
void Servo::setMaxDutyCycle(uint32_t _maxDutyCycle)
{
    maxDutyCycle = _maxDutyCycle;
}

/****f* Servo.h/getMaxDutyCycle()
  *  NAME
  *    getMaxDutyCycle() -- Rückgabe der Pulsweite für Winkelstellung 180°
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint32_t 
  ******
  * 
*/
uint32_t Servo::getMaxDutyCycle()
{
    return maxDutyCycle;
}



/****f* Servo.h/setWinkel()
  *  NAME
  *    setWinkel() -- setzen der Pulsweite für entsprechenden Winkel
  *  INPUTS
  *     uint8_t _winkel -- Wird ein Winkel größer 180 übergegeben, wird dieser auf 180 gesetzt
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void Servo::setWinkel(uint8_t _winkel)
{
    uint32_t range, duty_cycle;
    double resolution;
    double  dummy;

    setEnable(ON);
    if(_winkel > 180) _winkel = 180;

    winkel = _winkel;
    range = maxDutyCycle - minDutyCycle;
    resolution = (double)range / 180;

    dummy = resolution * (double)winkel;
    duty_cycle = (uint32_t)dummy + minDutyCycle;
    setDutyCycle(duty_cycle);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    setEnable(OFF);

}

/****f* Servo.h/getWinkel()
  *  NAME
  *    getWinkel() -- Rückgabe des Winkels
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint8_t winkel 
  ******
  * 
*/
uint8_t Servo::getWinkel()
{
    return winkel;
}
