#include "AnalogInput.h"
AnalogInput::AnalogInput()  {}

AnalogInput::~AnalogInput() {}

/****f* AnalogInput.h/setInputChannel()
  *  NAME
  *    setInputChannel() -- setzen des gewünschten Inputchannels
  *  INPUTS
  *     _channel
  *  RETURN VALUE
  *     NONE
  *  NOTES
  *     Dieser Methodenaufruf generiert den Dateipfad zum Auslesen 
  ******
  * 
*/
void AnalogInput::setInputChannel(AnalogInputChannel _channel)
{   
    channel = _channel;
    channelPath = "/sys/bus/iio/devices/iio:device0/in_voltage" + std::to_string(channel) + "_raw";
}

/****f* AnalogInput.h/readValue()
  *  NAME
  *    readValue() -- auslesen der ADCs aus dem entsprechenden Dateipfad
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     const uint16_t 
  ******
  * 
*/
uint16_t AnalogInput::readValue() const{
    std::fstream file(channelPath);
    uint16_t v = 0;
    file >> v;
    file.close();
    return v;
}


