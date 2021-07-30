

#include "stdafx.h"
#include "AnalogInput.h"

/****** InfraredSensor.h/State
 *  NAME
 *    State -- Alternatives for 0 and 1
******
*/
enum State
{
    OK = 0,
    SLOW_DOWN = 1,
    STOP = 2,
    ERROR = 3,
};

/****c* InfraredSensor.h/InfraredSensor
  *  NAME
  *    InfraredSensor -- 
  *  DESCRIPTION
  *    
  *  METHODS 
  *     setUpdateRate()
  *     getUpdateRate()
  *     watchSensor()
  *  ATTRIBUTES
  *     updateRate  -- Wie oft soll ausgelesen werden, bevor Mittelwert gebildet wird.
  *  NOTE
  *     Bei dieser Klasse handelt es sich um eine abgeleitete Klasse von AnalogInput. Alle Attribute und Methoden werden von AnalogInput an diese vererbt.
  ******
  * 
*/ 
class InfraredSensor: public AnalogInput 
{
    public:
        InfraredSensor();
        ~InfraredSensor();

    uint8_t updateRate = 50;


    void setUpdateRate(uint8_t _updateRate);
    uint8_t getUpdateRate();

    void watchSensor(volatile uint8_t*,volatile bool*);
};
