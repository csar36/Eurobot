#include "stdafx.h"
#include "Timer.h"
#include "AnalogInput.h"
#include "Motor.h"








/****c* Odometry.h/Odometry
  *  NAME
  *    Odometry 
  *  DESCRIPTION
  *        -- Hier werden die ADCs ausgelesen, welche an die Motorcontroller angeschlossen sind
  *  METHODS 
  *     ZeroPointAdjustment()
  *     setRepetitionRate()
  *     getRepetitionRate()
  *     superviseDriving()
  *  ATTRIBUTES
  *      RpmAdcRatio            -- Umrechnungsfaktor    
  *      PI                     
  *      diameterWheel
  *      repetitionRate         -- stellt den Schleifendurchlauf ein. In Abhängigkeit von dieser wird in Ecu die Pulsweite ehöht --> Einstellung der Beschleunigung
  *      zeroPoint              -- Spannungswert bei 0 min-1
  *  NOTES
  *      Bei dieser Klasse handelt es sich um eine abgeleitete Klasse von AnalogInput. Alle Attribute und Methoden werden von AnalogInput an diese vererbt.
  ******
  * 
*/ 
class Odometry: public AnalogInput
{
    public:
    Odometry();
    
    double RpmAdcRatio = 0.069521;      
    const float PI = 3.14159265359;
    float diameterWheel = 6.2;
    uint8_t repetitionRate;
    double  zeroPoint = 0;

    void ZeroPointAdjustment();
    void setRepetitionRate(uint8_t);
    uint8_t getRepetitionRate();
    void superviseDriving(volatile double*, volatile bool*, volatile bool*);
    
    
};
