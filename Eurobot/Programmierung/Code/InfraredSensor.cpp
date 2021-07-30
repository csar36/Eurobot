#include "InfraredSensor.h"


InfraredSensor::InfraredSensor(){}

InfraredSensor::~InfraredSensor(){}

/****f* InfraredSensor.h/setUpdateRate()
  *  NAME
  *    setUpdateRate() -- setzen der updateRate
  *  INPUTS
  *     _updateRate
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void InfraredSensor::setUpdateRate(uint8_t _updateRate)
{
    updateRate = _updateRate;
}

/****f* InfraredSensor.h/getUpdateRate()
  *  NAME
  *    getUpdateRate() -- Rückgabe der updateRate
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint8_t updateRate
  ******
  * 
*/
uint8_t InfraredSensor::getUpdateRate()
{
    return updateRate;
}

/****f* InfraredSensor.h/watchSensor()
  *  NAME
  *    watchSensor() -- Überwachen der Sensoren und setzen der States
  *  INPUTS
  *     volatile uint8_t* _state -- je nach State müssen Motoren weiter laufen, entschleunigen, anhalten
  *     volatile bool* _superviseInfrared -- False beendet diese Methode
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void InfraredSensor::watchSensor(volatile uint8_t* _state, volatile bool* _superviseInfrared)
{

    double dummy;
    uint32_t AdcValue = 0;

    while(*_superviseInfrared == true)
    {
        
            for(int i = 0; i < updateRate; i++)
                {
                    AdcValue += (uint16_t) readValue();
                }

                dummy = (double)AdcValue / updateRate;
                AdcValue = (uint32_t)dummy;
      
        if (AdcValue > 4096)
        {
          std::cout << "Fehler -> AdcVlaue ist größer als maximal erlaubt" << std::endl;
        }
    

        if(AdcValue < 4096 && AdcValue >= 2500)
        {
        *_state = STOP;
        // std::cout << "****** InraredSensor::watchSensor *******"<<std::endl;
       // std::cout << "        STOP          " << std::endl;
        }
        else if(AdcValue < 2500 && AdcValue >= 1300)
        {
        *_state = SLOW_DOWN;
        //std::cout << "****** InraredSensor::watchSensor *******"<<std::endl;
        //std::cout << "        SLOW_DOWN          " << std::endl;
        }
        else if(AdcValue < 1300)
        {
        *_state = OK;
        }
        else
        {
         *_state = ERROR;
        }

    }
   
}





