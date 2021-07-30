#include "Odometry.h"

Odometry::Odometry()   {}



/****f* Odometry.h/ZeroPointAdjustment()
  *  NAME
  *    ZeroPointAdjustment() -- ADC Mittelwertbildung bei nicht drehenden Motoren
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void Odometry::ZeroPointAdjustment()
{
    uint64_t valueCount = 0;

    for(int i =0;i < 5000;i++)
    {
        valueCount  += readValue();
        
    }
    zeroPoint = (double) valueCount / 5000;

}

/****f* Odometry.h/setRepetitionRate()
  *  NAME
  *    setRepetitionRate() -- Einstellung des Schleifendurchlaufes für superviseDriving()
  *  INPUTS
  *     _repetitionRate -- Anzahl der Schleifendurchläufe
  *  RETURN VALUE
  *     NONE
  *  NOTE
  *     Die RepetitionRate beeinflusst gleichzeitig auch das Beschleunigungsverhalten, da in Ecu nach jeden fertigen Schleifendurchlauf
  *     beim be- und entschleunigen die Pulsweite verändert wird
  ******
  * 
*/
void Odometry::setRepetitionRate(uint8_t _repeitionRate)
{
    repetitionRate = _repeitionRate;
}

/****f* Odometry.h/getRepetitionRate()
  *  NAME
  *    getRepetitionRate() -- Rückgabe der repetitionRate
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     uint8_t repetetionRate
  ******
  * 
*/
uint8_t Odometry::getRepetitionRate()
{
    return repetitionRate;
}

/****f* Odometry.h/superviseDriving()
  *  NAME
  *    superviseDriving() -- Ließt den ADC Wert aus und misst die Zeit um gefahrene Strecke zu berechnen
  *  INPUTS
  *    volatile double* _strecke -- zurückgelegte Strecke wird im Orginal beschrieben
  *    volatile bool* _supervise -- sobald diese auf false gesetzt ist, schließt die Funktion ab
  *    volatile bool* _update -- Teilt mit, wann die Strecke von dieser Funktion berechnet wurde
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void Odometry::superviseDriving(volatile double* _strecke, volatile bool* _supervise, volatile bool* _update)
{
    Timer deltaTimer;
    uint64_t valueCount = 0;
    double averageAdc;
    double currentRpm;

      while(*_supervise == true)
      {
            deltaTimer.startTimer();                                                    
            valueCount = 0;

                 for(int i = 0; i< repetitionRate; i++)
                {
                    valueCount += readValue();
                }        
                    averageAdc = (double) valueCount / repetitionRate;                      
                    currentRpm = (averageAdc - zeroPoint) * RpmAdcRatio;              
                    currentRpm = abs(currentRpm);                                                           
                    *_strecke  += currentRpm *  (deltaTimer.getTime(sec)/60) * PI * diameterWheel;     
                    *_update = true;                                                 
    }                      
    
    return;
}

