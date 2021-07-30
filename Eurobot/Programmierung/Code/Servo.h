#ifndef SERVO_H
#define SERVO_H


#include "stdafx.h"
#include "Pwm.h"

 /****c* Servo.h/Servo
  *  NAME
  *    Servo 
  *  DESCRIPTION
  *    Diese Klasse ist eine abgeleitete Klasse von PWM. Alle Attribute und Methoden von PWM sind somit Bestandteil dieser Klasse
  *    Klasse zur Ansteuerung eines Servomotors
  *  METHODS 
  *     setMinDutyCycle()
  *     getMinDutyCycle()
  *     setMaxDutyCycle()
  *     getMaxDutyCycle()
  *     setWinkel()
  *     getWinkel() 
  *  ATTRIBUTES
  *     minDutyCycle     - Value der Pulsweite für 0° Stellung
  *     maxDutyCycle     - Value der Pulsweite für 180° Stellung
  *     winkel           - der zufahrende Winkel
  *     
  *  NOTES
  *     Sofern der Servo auf die übergebende Winkelstellung gefahren und gehalten werden soll, muss dies mit dem Methodenaufruf der PWM .setEnable(ON) geschehen
  * 
  ******
  * 
*/ 
class Servo: public PWM
{


    public:

        Servo();
        ~Servo();

        uint32_t minDutyCycle;
        uint32_t maxDutyCycle;
        uint8_t winkel;
        
        void setMinDutyCycle(uint32_t _minDutyCycle);
        uint32_t getMinDutyCycle();
        
        void setMaxDutyCycle(uint32_t _maxDutyCycle);
        uint32_t getMaxDutyCycle();

        void setWinkel(uint8_t _winkel);
        uint8_t getWinkel();


    
        
};



#endif     
         