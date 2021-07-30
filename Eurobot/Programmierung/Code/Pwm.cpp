#include "Pwm.h"

PWM::PWM() {}


/****f* Pwm.h/getPWMPath()
  *  NAME
  *    getPWMPath() -- Diese Methode wird benötigt, um die Pfade zur Einstellung der PWM zu generieren
  *  INPUTS
  *     _pin -- Übergabe der genutzten PWM
  *  RETURN VALUE
  *     string -- Rückgabe Teil des Ordnerpfades
  *  NOTE
  *     P9_22 -> PWM-1:0
  *     P9_21 -> PWM-1:1
  *     P9_14 -> PWM-4:0
  *     P9_16 -> PWM-4:1
  *     P8_19 -> PWM-7:0
  *     P8_13 -> PWM-7:1
  ******
  * 
*/
std::string PWM::getPWMPath(PWMPin _pin)
{
    switch(_pin)
    {
        case 0: return "1/pwm-1:0";   //P9_22 -> PWM-1:0
        case 1: return "1/pwm-1:1";   //P9_21 -> PWM-1:1
        case 2: return "4/pwm-4:0";    //P9_14 -> PWM-4:0
        case 3: return "4/pwm-4:1";    //P9_16 -> PWM-4:1
        case 4: return "7/pwm-7:0";    //P8_19 -> PWM-7:0
        case 5: return "7/pwm-7:1";    //P8_13 -> PWM-7:1
        default: return "Fehler";
    }
}

/****f* Pwm.h/setPin()
  *  NAME
  *    setPin() -- Ausführen der config-pin Anweisung
  *  INPUTS
  *     _m_pin  -- Pin welcher als PWM konfiguriert werden soll
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void PWM::setPin(PWMPin _m_pin)
{
    m_pin = _m_pin;
    std::string PinConfig = "config-pin ";
    switch(m_pin)
    {
        case P9_22: 
            PinConfig += "P9_22 pwm";
            system(PinConfig.c_str()); break; 
        case P9_21: 
            PinConfig += "P9_21 pwm";
            system(PinConfig.c_str()); break; 
        case P9_14: 
            PinConfig += "P9_14 pwm";
            system(PinConfig.c_str()); break; 
        case P9_16: 
            PinConfig += "P9_16 pwm";
            system(PinConfig.c_str()); break; 
        case P8_19: 
            PinConfig += "P8_19 pwm";
            system(PinConfig.c_str()); break; 
        case P8_13: 
            PinConfig += "P8_13 pwm";
            system(PinConfig.c_str()); break;
        default: break;
    }

    periodPath = PWM_PATH + getPWMPath(_m_pin) + "/period";
    dutyCyclePath =  PWM_PATH + getPWMPath(m_pin) + "/duty_cycle";
    enablePath = PWM_PATH + getPWMPath(m_pin) + "/enable";


}

/****f* Pwm.h/exportPWM()
  *  NAME
  *    exportPWM() -- zum Exportieren des jeweiligen PWM-Moduls 
  *  INPUTS
  *     _m_pin 
  *  RETURN VALUE
  *     NONE
  *  NOTE
  *     Es wird überprüft ob der jeweilige Ordnerpfad existiert, falls ja wird die PWM nicht nochmals exportiert, sonst Segmatation Fault
  ******
  * 
*/
void PWM::exportPWM(PWMPin _m_pin)
{
    std::string PWM_export = PWM_PATH + getPWMPath(_m_pin);

    DIR *pDir;
    bool bExists = false;

    pDir = opendir(PWM_export.c_str());

    if (pDir != NULL)
    {
            bExists = true;
            closedir (pDir);
    }

    if(bExists == false)
    {
        switch(_m_pin)
        {
            case P9_22: 
                PWM_export = "echo 0 > ";
                PWM_export += PWM_PATH;
                PWM_export += "1/export";
                system(PWM_export.c_str()); break; 
            case P9_21: 
                PWM_export = "echo 1 > ";
                PWM_export += PWM_PATH;
                PWM_export += "1/export";
                system(PWM_export.c_str()); break; 
            case P9_14: 
                PWM_export = "echo 0 > ";
                PWM_export += PWM_PATH;
                PWM_export += "4/export";
                system(PWM_export.c_str()); break; 
            case P9_16: 
                PWM_export = "echo 1 > ";
                PWM_export += PWM_PATH;
                PWM_export += "4/export";
                system(PWM_export.c_str()); break; 
            case P8_19: 
                PWM_export = "echo 0 > ";
                PWM_export += PWM_PATH;
                PWM_export += "7/export";
                system(PWM_export.c_str()); break; 
            case P8_13: 
                PWM_export = "echo 1 > ";
                PWM_export += PWM_PATH;
                PWM_export += "7/export";
                system(PWM_export.c_str()); break;
                default: break;
        }
    

    }
}


/****f* Pwm.h/getPin()
  *  NAME
  *    getPin() -- Rückgabe des gesetzten Pins für die jeweilige PWM
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     PWMPin m_pin
  ******
  * 
*/
PWMPin PWM::getPin()
{
    return m_pin;
}

/****f* Pwm.h/setPeriod()
  *  NAME
  *    setPeriod() -- setzen der Periode
  *  INPUTS
  *     _period
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void PWM::setPeriod(uint32_t _period)
{
    period = _period;
    std::fstream fs(periodPath);
    fs << _period;
    fs.close();
}

/****f* Pwm.h/getPeriod()
  *  NAME
  *    getPeriod() -- Rückgabe der eingestellten Periode 
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint32_t period
  ******
  * 
*/
uint32_t PWM::getPeriod()
{    
    std::fstream fs(periodPath);
    fs >> period;
    fs.close();
    return period;
}

/****f* Pwm.h/setDutyCycle()
  *  NAME
  *    setDutyCycle() -- Setzen des Pulsweite
  *  INPUTS
  *     _duty_cycle
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void PWM::setDutyCycle(uint32_t _duty_cycle)
{
    
    duty_cycle = _duty_cycle;
    std::fstream fs(dutyCyclePath); 
    fs << _duty_cycle;
    fs.close();
}

/****f* Pwm.h/getDutyCycle()
  *  NAME
  *    getDutyCycle() -- Rückgabe der Pulsweite
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint32_t duty_cycle 
  ******
  * 
*/
uint32_t PWM::getDutyCycle()
{    
    PWMPin _m_pin = m_pin;
    std::fstream fs(dutyCyclePath);
    fs >> duty_cycle;
    fs.close();
    return duty_cycle;
}

/****f* Pwm.h/setEnable()
  *  NAME
  *    setEnable() -- starten der PWM
  *  INPUTS
  *     _pwmEn -- ON = 1; OFF = 0
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void PWM::setEnable(PWMEn _pwmEn)
{ 
    PWMPin _m_pin = m_pin;
    std::fstream fs(enablePath);
    fs << _pwmEn;
    fs.close();
}

/****f* Pwm.h/getEnable()
  *  NAME
  *    getEnable() -- Rückgabe ob PWM aktiv ist
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     bool
  ******
  * 
*/
bool PWM::getEnable()
{   
    bool en;
    std::fstream fs(enablePath);
    fs >> en;
    fs.close();
    return en;
}
