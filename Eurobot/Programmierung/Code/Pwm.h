#ifndef PWM_H
#define PWM_H
#include "stdafx.h"
//#include "ctime"


#define PWM_PATH "/sys/class/pwm/pwmchip"



/****** Pwm.h/PWMEn
 *  NAME
 *    PWMEn -- Alternatives for 0 and 1
******
*/
enum PWMEn
    {
        OFF = 0,
        ON = 1,
    };

/****** Pwm.h/PWMPin
 *  NAME
 *      PWMPin -- Enum to generate StringPaths
 *      P9_22 -- PWM-1:0
 *      P9_21 -- PWM-1:1
 *      P9_14 -- PWM-4:0
 *      P9_16 = 3 -- PWM-4:1
 *      P8_19 = 4 -- PWM-7:0
 *      P8_13 = 5 -- PWM-7:1  
******
*/
enum PWMPin
{
    P9_22 = 0,          // PWM-1:0
    P9_21 = 1,          // PWM-1:1
    P9_14 = 2,          // PWM-4:0
    P9_16 = 3,          // PWM-4:1
    P8_19 = 4,          // PWM-7:0
    P8_13 = 5,          // PWM-7:1    
    PWM_IDLE = 10,
};

 /****c* Pwm.h/PWM
  *  NAME
  *    PWM -- This class provides operations to control the pwm moduls on the beaglebone black
  *  DESCRIPTION
  *    The class PWM is an interface between the developed software and the beaglebone black.
  *    It provides operations to control the pwm modul of the beaglebone black. 
  *    Furthermore it provides attributes with the values of last known status of the pwm
  *  METHODS
  *  setPin()
  *  exportPWM()
  *  getPin()
  *  setPeriod()
  *  getPeriod()
  *  setDutyCycle()
  *  getDutyCycle()
  *  setEnable()
  *  getEnable()
  *  getPWMPath()
  *  ATTRIBUTES
  *  m_pin         
  *  period
  *  duty_cycle
  *  periodPath
  *  dutyCyclePath
  *  enablePath
  * 
  *  NOTES
  *  Bei dieser Klasse handelt es sich um eine Basisklasse. Diese wird an andere Klassen vererbt
  * 
  *
  ******
  * 
  */ 
class PWM
{
  
public:
    PWM();  

    void setPin(PWMPin _m_pin);
    void exportPWM(PWMPin _m_pin);
    PWMPin getPin();
    void setPeriod(uint32_t);
    uint32_t getPeriod(void);
    void setDutyCycle(uint32_t);
    uint32_t getDutyCycle();
    void setEnable(PWMEn _pwmEn);
    bool getEnable();
    std::string getPWMPath(PWMPin);

private:
    PWMPin m_pin;
    uint32_t period;
    uint32_t duty_cycle;
    std::string periodPath;
    std::string dutyCyclePath;
    std::string enablePath;
};
#endif

    