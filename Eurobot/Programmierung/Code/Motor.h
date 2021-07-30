#ifndef _MOTOR_H
#define _MOTOR_H
#include "gpio.h"
#include "Pwm.h"
#include "string"





 /****c* motor.h/MOTOR
  *  NAME
  *    MOTOR -- Child of StateMachine, controlls the states of a motor. 
  *  USAGE
  *    MOTOR 
  *  DESCRIPTION
  *    The class MOTOR is a State Machine it has the states Idle, Stop, Start, ChangeSpeed and ChangePin.
  *  METHODS
  *     MotorStart();
  *     MotorStop();
  *  ATTRIBUTES
  *     enablePin    - Value to address the corresponding GPIO pin.
  *     directionPin - Value to address the corresponding GPIO pin. 
  ******
  * 
  */ 
class MOTOR: public PWM
{
public:
    GPIO enablePin;
    GPIO directionPin;
 
public:
    MOTOR();
 

    void MotorStart();
    void MotorStop();

   

private:
    
};

#endif
