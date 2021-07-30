#include "Motor.h"

MOTOR::MOTOR() {}


/****f* Motor.h/MotorStart()
  *  NAME
  *    MotorStart() -- Starten des Motors
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void MOTOR::MotorStart()
{
  setEnable(ON);
  enablePin.gpioSetValue(HIGH);
}

/****f* Motor.h/MotorStop()
  *  NAME
  *    MotorStop() -- Stoppen des Motors
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     NONE 
  ******
  * 
*/
void MOTOR::MotorStop()
{
  setEnable(OFF);
  enablePin.gpioSetValue(LOW);
}
