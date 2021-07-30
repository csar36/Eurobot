#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include "stdafx.h"


/****** AnalogInput.h/AnalogInputChannel
 *  NAME
 *      AnalogInputChannel -- Enum zum generieren Pfad ADC 
******
*/
enum AnalogInputChannel {
    ANALOG_INPUT_0 = 0,
    ANALOG_INPUT_1,
    ANALOG_INPUT_2,
    ANALOG_INPUT_3,
    ANALOG_INPUT_4,
    ANALOG_INPUT_5,
    ANALOG_INPUT_6,
};

 /****c* AnalogInput.h/AnalogInput
  *  NAME
  *    AnalogInput -- 
  *  DESCRIPTION
  *    
  *  METHODS 
  *         setInputChannel()
  *         readValue() 
  *  ATTRIBUTES
  *         channel       
  *         channelPath
  *     
  *  NOTES
  *         Bei dieser Klasse handelt es sich um eine Basisklasse, die mit Odometry und InfraredSensor verebt wurde
  *
  ******
  * 
*/ 
class AnalogInput
{
 
public:
    AnalogInput();
    ~AnalogInput();
    

    AnalogInputChannel channel;
    std::string channelPath;

    void setInputChannel(AnalogInputChannel);
    uint16_t readValue() const;
};

#endif 
