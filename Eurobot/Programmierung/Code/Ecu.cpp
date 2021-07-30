#include "stdafx.h"
#include "Ecu.h"


Ecu::Ecu() {}



Ecu::~Ecu() {}

/****f* Ecu.h/configMotorRight()
  *  NAME
  *    configMotorRight() -- setzt enablePin, directionPin, PWMPin und Periode des rechten Motors
  *  INPUTS
  *     _enablePin -- Gpio Pin auf dem die Freigabe gesetzt werden soll
  *     _directionPin -- Gpio Pin auf dem die Richtung gesetzt werden soll
  *     _period -- Periode der PWM; Im Laufe der Projektarbeit immer auf 2.000.000 gesetzt
  *  RETURN VALUE
  *     NONE
  ******
  * 
  */
void Ecu::configMotorRight(GPIOPin _enablePin, GPIOPin _directionPin, PWMPin _pwmpin, uint32_t _period)
{
        
      
        MotorRight.enablePin.gpioSetPin(_enablePin);
        MotorRight.enablePin.gpioSetDirection(PIN_OUT);
        MotorRight.directionPin.gpioSetPin(_directionPin);
        MotorRight.directionPin.gpioSetDirection(PIN_OUT);
        MotorRight.setPin(_pwmpin);
        MotorRight.setPeriod(_period);
        
}

/****f* Ecu.h/configMotorLeft()
  *  NAME
  *    configMotorLeft() -- setzt enablePin, directionPin, PWMPin und Periode des linken Motors
  *  INPUTS
  *     _enablePin -- Gpio Pin auf dem die Freigabe gesetzt werden soll
  *     _directionPin -- Gpio Pin auf dem die Richtung gesetzt werden soll
  *     _period -- Periode der PWM; Im Laufe der Projektarbeit immer auf 2.000.000 gesetzt
  *  RETURN VALUE
  *     NONE
  ******
  * 
  */
void Ecu::configMotorLeft(GPIOPin _enablePin, GPIOPin _directionPin, PWMPin _pwmpin, uint32_t _period)
{
        
        MotorLeft.enablePin.gpioSetPin(_enablePin);
        MotorLeft.enablePin.gpioSetDirection(PIN_OUT);
        MotorLeft.directionPin.gpioSetPin(_directionPin);
        MotorLeft.directionPin.gpioSetDirection(PIN_OUT);
        MotorLeft.setPin(_pwmpin);
        MotorLeft.setPeriod(_period);
}

/****f* Ecu.h/configRegulatorRight()
  *  NAME
  *    configRegulatorRight() -- setzt den AnlogInput für das Einlesen der rechten Drehzahl; berechnet ADC-Mittelwert bei 0min-1
  *  INPUTS
  *     _channel 
  *  RETURN VALUE
  *     NONE
  ******
  * 
  */
void Ecu::configRegulatorRight(AnalogInputChannel _channel)
{
   RegulatorRight.setInputChannel(_channel);
   RegulatorRight.ZeroPointAdjustment();
   std::cout << "Nullpunkt ADC: "<< RegulatorRight.zeroPoint << std::endl;
}

/****f* Ecu.h/configRegulatorLeft()
  *  NAME
  *    configRegulatorLeft() -- setzt den AnlogInput für das Einlesen der linken Drehzahl; berechnet ADC-Mittelwert bei 0min-1
  *  INPUTS
  *     _channel
  *  RETURN VALUE
  *     just 0
  ******
  * 
  */
void Ecu::configRegulatorLeft(AnalogInputChannel _channel)
{
    RegulatorLeft.setInputChannel(_channel);
    RegulatorLeft.ZeroPointAdjustment();
    std::cout << "Nullpunkt ADC: "<< RegulatorLeft.zeroPoint << std::endl;
    
}

/****f* Ecu.h/configInfraredSensors()
  *  NAME
  *    configInfraredSensors() -- setzen der AnlogInputs für die jeweiligen Infrarotsensoren
  *  INPUTS
  *     _FrontLeft
  *     _FrontRight
  *     _BackLeft
  *     _BackRight
  *  RETURN VALUE
  ******
  * 
  */
void Ecu::configInfraredSensors(AnalogInputChannel _FrontLeft, AnalogInputChannel _FrontRight, AnalogInputChannel _BackLeft, AnalogInputChannel _BackRight)
{       
        InfraredSensor_FrontLeft.setInputChannel(_FrontLeft);
        InfraredSensor_FrontRight.setInputChannel(_FrontRight);
        InfraredSensor_BackLeft.setInputChannel(_BackLeft);
        InfraredSensor_BackRight.setInputChannel(_BackRight);
}

/****f* Ecu.h/driveForward()
  *  NAME
  *    driveForward() -- setzt die Drehrichtung der Motoren, setzt die Beschleunigung über repititionRate, startet die jeweilgen Threads
  *  INPUTS
  *     _distance
  *     _speed
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
void Ecu::driveForward(double _distance, uint8_t _speed)
{   

        uint8_t repetitionRate;
            
        std::cout << "Ecu::driveForward -- Zu fahrende Strecke: " << _distance << std::endl;


        distanceLeft = 0;
        distanceRight = 0;    
                                                                                                                                                                                    //MotorRight:   Low -> Backward, High -> Forward
        MotorRight.directionPin.gpioSetValue(HIGH);      
        MotorLeft.directionPin.gpioSetValue(LOW);        
        
        repetitionRate = 25; 
        RegulatorLeft.setRepetitionRate(repetitionRate);
        RegulatorRight.setRepetitionRate(repetitionRate);
        
        std::thread t_InfraredSensor_FrontLeft(&InfraredSensor::watchSensor, this->InfraredSensor_FrontLeft, p_StateInfraredSensor_FrontLeft, p_superviseInfrared);
        std::thread t_InfraredSensor_FrontRight(&InfraredSensor::watchSensor, this->InfraredSensor_FrontRight, p_StateInfraredSensor_FrontRight, p_superviseInfrared);
   
        std::thread t_MotorLeft(&Odometry::superviseDriving, this->RegulatorLeft,  p_distanceLeft, p_superviseOdometry, p_updateLeftOdometry);
        std::thread t_MotorRight(&Odometry::superviseDriving, this->RegulatorRight,  p_distanceRight, p_superviseOdometry, p_updateRightOdometry);
        std::thread t_ControlMotors(&Ecu::controlMotorsStraight, this, _distance, _speed, p_StateInfraredSensor_FrontLeft, p_StateInfraredSensor_FrontRight);

        superviseInfrared = true;
        superviseOdometry = true;

        t_InfraredSensor_FrontLeft.detach();
        t_InfraredSensor_FrontRight.detach();

        t_MotorRight.detach();
        t_MotorLeft.detach();
        t_ControlMotors.join();


        double gefahren = (distanceRight + distanceLeft) / 2;

         std::cout << "**********************" << std::endl;
        std::cout << "State Sensor Left: " << (double)StateInfraredSensor_FrontLeft << std::endl;
        std::cout << "State Sensor Right: " << (double)StateInfraredSensor_FrontRight << std::endl;
        std::cout << "**********************" << std::endl;

        std::cout << "Gefahrene Strecke : " << gefahren << std::endl;
    
        superviseInfrared = false;
        superviseOdometry = false;
        std::cout << "Gefahrene Strecke Links: " << distanceLeft << std::endl;
        std::cout << "Gefahrene Strecke Rechts: " << distanceRight << std::endl;
        std::cout << "________________________________________________" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


/****f* Ecu.h/driveBackward()
  *  NAME
  *    driveBackward() -- setzt die Drehrichtung der Motoren, setzt die Beschleunigung über repititionRate, startet die jeweilgen Threads
  *  INPUTS
  *     _distance
  *     _speed
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
void Ecu::driveBackward(double _distance, uint8_t _speed)
{    
        uint8_t repetitionRate;

        std::cout << "Ecu::driveBackward -- Zu fahrende Strecke: " << _distance << std::endl;

        distanceLeft = 0;
        distanceRight = 0; 
                                                                     
        MotorRight.directionPin.gpioSetValue(LOW);      
        MotorLeft.directionPin.gpioSetValue(HIGH);        
        
        repetitionRate = 25; 
        RegulatorLeft.setRepetitionRate(repetitionRate);
        RegulatorRight.setRepetitionRate(repetitionRate);

        superviseInfrared = true;
   
        std::thread t_InfraredSensor_BackLeft(&InfraredSensor::watchSensor, this->InfraredSensor_BackLeft, p_StateInfraredSensor_BackLeft, p_superviseInfrared);
        std::thread t_InfraredSensor_BackRight(&InfraredSensor::watchSensor, this->InfraredSensor_BackRight, p_StateInfraredSensor_BackRight, p_superviseInfrared);

        superviseOdometry = true;
        std::thread t_MotorLeft(&Odometry::superviseDriving, this->RegulatorLeft,  p_distanceLeft, p_superviseOdometry, p_updateLeftOdometry);
        std::thread t_MotorRight(&Odometry::superviseDriving, this->RegulatorRight,  p_distanceRight, p_superviseOdometry, p_updateRightOdometry);
        std::thread t_ControlMotors(&Ecu::controlMotorsStraight, this, _distance, _speed, p_StateInfraredSensor_BackLeft, p_StateInfraredSensor_BackRight);
       
        t_InfraredSensor_BackLeft.detach();
        t_InfraredSensor_BackRight.detach();


        t_MotorRight.detach();
        t_MotorLeft.detach();
        t_ControlMotors.join();


        double gefahren = (distanceRight + distanceLeft) / 2;
        std::cout << "**********************" << std::endl;
        std::cout << "State Sensor Left: " << (double)StateInfraredSensor_BackLeft << std::endl;
        std::cout << "State Sensor Right: " << (double)StateInfraredSensor_BackRight << std::endl;
        std::cout << "**********************" << std::endl;

        std::cout << "Gefahrene Strecke : " << gefahren << std::endl;
        superviseInfrared = false;
        superviseOdometry = false;
        std::cout << "Gefahrene Strecke Links: " << distanceLeft << std::endl;
        std::cout << "Gefahrene Strecke Rechts: " << distanceRight << std::endl;
        std::cout << "________________________________________________" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

/****f* Ecu.h/driveAngle()
  *  NAME
  *    driveAngle() -- berechnet den zu fahrenden Weg, setzt die Beschleunigung über repititionRate, startet die jeweiligen Threads
  *  INPUTS
  *     _angle
  *     _directionOfRotation -- "-cw" "-ccw"
  *  RETURN VALUE
  *     just 0
  *  IDEAS
  *     The return value could be used for error handling 
  ******
  * 
  */
void Ecu::driveAngle(double _angle, std::string _directionOfRotation)
{
        uint8_t repetitionRate;
        double distance;
        double angle = _angle;

        if(_angle <= 90)
        {
                wheelSpace = 25.179;
        }
        else if(_angle <=180)
        {
                wheelSpace = 26.1;
        }
        else 
        {
                wheelSpace = 26.35;
        }
        

        distanceLeft = 0;
        distanceRight = 0; 

        distance = (_angle/360)  * PI * wheelSpace;
        std::cout <<"Ecu::driveAngle -- Zu fahrende Strecke:  " << distance << std::endl;

        repetitionRate = 30; 
        RegulatorLeft.setRepetitionRate(repetitionRate);
        RegulatorRight.setRepetitionRate(repetitionRate);

     


        if(_directionOfRotation == "-cw")
        {
                MotorRight.directionPin.gpioSetValue(LOW);      
                MotorLeft.directionPin.gpioSetValue(LOW);        
        }
        else if(_directionOfRotation == "-ccw")
        {
                MotorRight.directionPin.gpioSetValue(HIGH);      
                MotorLeft.directionPin.gpioSetValue(HIGH);                
        }
        else
        {
                std::cout << "Fehler in der Drehrichtungsübergabe"<< std::endl;
                return;
        }


        std::thread t_MotorLeft(&Odometry::superviseDriving, this->RegulatorLeft,  p_distanceLeft, p_superviseOdometry, p_updateLeftOdometry);
        std::thread t_MotorRight(&Odometry::superviseDriving, this->RegulatorRight,  p_distanceRight, p_superviseOdometry, p_updateRightOdometry);
        std::thread t_ControlMotorsAngle(&Ecu::controlMotorsAngle, this, distance);
        superviseOdometry = true;

        t_MotorRight.detach();
        t_MotorLeft.detach();
        t_ControlMotorsAngle.join();

        superviseOdometry = false;

        std::cout << "Winkelstellung abgeschlossen" << std::endl;
        std::cout << "Gefahrene Strecke Links: " << distanceLeft << std::endl;
        std::cout << "Gefahrene Strecke Rechts: " << distanceRight << std::endl;
        std::cout << "________________________________________________" << std::endl;

        StateInfraredSensor_FrontLeft = 0;
        StateInfraredSensor_FrontRight = 0;
        StateInfraredSensor_BackLeft = 0;
        StateInfraredSensor_BackRight = 0;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

/****f* Ecu.h/driveCircula()
  *  NAME
  *    driveCircula() -- berechnet den Weg um kreisförmige Fahrten durchführen zu können, stellt entsprechend die Drehrichtung Motoren und führt Threads aus
  *  INPUTS
  *     _radius -- Radius des Kreises
  *     _angle --  Winkel des Kreises
  *     _direction -- Vorwärts oder Rückwärts
  *     _directionOfRotation -- cw ccw
  *  RETURN VALUE
  *     just 0
  *  ERROR
  *     Die Motoren müssen unterschiedlich schnell laufen. Es gibt ein Problem beim Berechen der Geschwindigkeiten 
  ******
  * 
  */
void Ecu::driveCircula(double _radius, double _angle, std::string _direction, std::string _directionOfRotation)
{
        double distanceToDriveLeft;
        double distanceToDriveRight;
        double ratioForSpeed;
        double dummy;
        uint8_t speedRight;
        uint8_t speedLeft;
        volatile uint8_t* p_StateInfraredLeft;
        volatile uint8_t* p_StateInfraredRight;
        

        if(_direction == "-forward" && _directionOfRotation == "-cw")
        {
                MotorRight.directionPin.gpioSetValue(HIGH);      
                MotorLeft.directionPin.gpioSetValue(LOW);        
        
                distanceToDriveRight = (_angle/360) * 2 * PI * _radius;
                distanceToDriveLeft =  (_angle/360) * 2 * PI * (_radius + wheelSpace);
                ratioForSpeed = distanceToDriveRight / distanceToDriveLeft;
                std::cout << "Distance to drive Left:" << distanceToDriveLeft << "Distance to drive right" <<distanceToDriveRight <<std::endl;

                speedLeft = 40;
                dummy = (double) 80 * ratioForSpeed;
                speedRight = (uint8_t) dummy; 
        }
        else if(_direction == "-forward" && _directionOfRotation == "-ccw")
        {
                MotorRight.directionPin.gpioSetValue(HIGH);      
                MotorLeft.directionPin.gpioSetValue(LOW);  

                distanceToDriveLeft = (_angle/360) * 2 * PI * _radius;
                distanceToDriveRight =  (_angle/360) * 2 * PI * (_radius + wheelSpace);
                ratioForSpeed =  distanceToDriveLeft / distanceToDriveRight;
                dummy = (double)40 * ratioForSpeed;
                speedRight = 40;
                speedLeft = (uint8_t) dummy;
        }
        else if(_direction == "-backward" && _directionOfRotation == "-cw")
        {
                MotorRight.directionPin.gpioSetValue(LOW);      
                MotorLeft.directionPin.gpioSetValue(HIGH);   

                distanceToDriveLeft = (_angle/360) * 2 * PI * _radius;
                distanceToDriveRight =  (_angle/360) * 2 * PI * (_radius + wheelSpace);
                ratioForSpeed =  distanceToDriveLeft / distanceToDriveRight;
                dummy = (double)40 * ratioForSpeed;
                speedRight = 40;
                speedLeft = (uint8_t) dummy;
        }
        else if(_direction == "-backward" && _directionOfRotation == "-ccw")
        {
                MotorRight.directionPin.gpioSetValue(LOW);      
                MotorLeft.directionPin.gpioSetValue(HIGH); 

                distanceToDriveRight = (_angle/360) * 2 * PI * _radius;
                distanceToDriveLeft =  (_angle/360) * 2 * PI * (_radius + wheelSpace);
                ratioForSpeed = distanceToDriveRight / distanceToDriveLeft;
                dummy = (double)40 * ratioForSpeed;
                speedLeft = 40;
                speedRight = (uint8_t) dummy;         
        }
        else{
                std::cout << "Fehler in der Parameterübergabe" << std::endl;
                return;
        }

        superviseOdometry = true;
        std::thread t_MotorLeft(&Odometry::superviseDriving, this->RegulatorLeft,  p_distanceLeft, p_superviseOdometry, p_updateLeftOdometry);
        std::thread t_MotorRight(&Odometry::superviseDriving, this->RegulatorRight,  p_distanceRight, p_superviseOdometry, p_updateRightOdometry);
        std::thread t_ControlMotorsCirculaTrip(&Ecu::controlMotorsCircula, this, distanceToDriveLeft, distanceToDriveRight, speedLeft, speedRight);



        t_MotorLeft.detach();
        t_MotorRight.detach();
        t_ControlMotorsCirculaTrip.join();

    
        superviseInfrared = false;
        std::cout << "drived distance Left: " << distanceLeft << "drived distance right: " << distanceRight << std::endl;



}

/****f* Ecu.h/controlMotorsStraight()
  *  NAME
  *    controlMotorsStraight() -- Regelt die Geschwindigkeiten der Motoren
  *  INPUTS
  *     _distance
  *     _speed
  *     _p_infraredLeft
  *     _p_infraredRight
  *  RETURN VALUE
  *     NONE
  ******
  * 
  */
void Ecu::controlMotorsStraight(double _distance, uint8_t _speed, volatile uint8_t* _p_InfraredLeft, volatile uint8_t* _p_InfraredRight)
{
        uint32_t pulsweite;
        uint32_t endPulsweite, startPulsweite;
        uint32_t deltaPulsweite;
        double speed = (double) _speed/100 * MotorLeft.getPeriod();
        double drivedDistance = 0;
        double alreadyDrived = 0;

        endPulsweite = (uint32_t) speed;
        pulsweite = (uint32_t)MotorLeft.getPeriod() * 0.1;
        startPulsweite = pulsweite;
        deltaPulsweite = (uint32_t)MotorLeft.getPeriod() * 0.01;
        superviseOdometry = true;
        MotorLeft.setDutyCycle(pulsweite);
        MotorRight.setDutyCycle(pulsweite);
        MotorRight.MotorStart();
        MotorLeft.MotorStart();
        

       
        while (pulsweite <= endPulsweite && drivedDistance < _distance/2 && *_p_InfraredLeft == 0 && *_p_InfraredRight == 0)
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        pulsweite += deltaPulsweite;
                        MotorRight.setDutyCycle(pulsweite); 
                        MotorLeft.setDutyCycle(pulsweite);
                        drivedDistance =  (distanceLeft + distanceRight) / 2;     
                }

        }
            
        alreadyDrived = drivedDistance;
        //std::cout << "Gefahrene Distanz: " << drivedDistance << std::endl;

  
        while (drivedDistance < (_distance - alreadyDrived) && *_p_InfraredLeft == 0 && *_p_InfraredRight == 0)
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        drivedDistance =  (distanceLeft + distanceRight) / 2;
                }
        }
                    

        while(drivedDistance < _distance && pulsweite >= startPulsweite && (*_p_InfraredLeft == 0 || *_p_InfraredLeft == 1) && (*_p_InfraredRight == 0 || *_p_InfraredRight == 1))
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        pulsweite -= deltaPulsweite;
                        MotorRight.setDutyCycle(pulsweite); 
                        MotorLeft.setDutyCycle(pulsweite);
                        drivedDistance =  (distanceLeft + distanceRight) / 2;
                        
                                            
                }
        }

        MotorLeft.MotorStop();
        MotorRight.MotorStop();
        //std::cout << "In ECU -> gefahrene Distanz rechts: "<<distanceRight << "Gefahrene Distanz Links "<< distanceLeft << std::endl;

        return;
}
 
/****f* Ecu.h/controlMotorsAngle()
  *  NAME
  *    controlMotorsAngle() -- SRegelt die Geschwindigkeiten der Motoren
  *  INPUTS
  *     _distance
  *  RETURN VALUE
  *     NONE
  ******
  * 
  */
void Ecu::controlMotorsAngle(double _distance)
{
        uint32_t pulsweite;
        uint32_t endPulsweite, startPulsweite;
        uint32_t deltaPulsweite;
        double speed = (double) 0.3 * MotorLeft.getPeriod();

        double drivedDistance = 0;
        double alreadyDrived = 0;

        endPulsweite = (uint32_t) speed;
        pulsweite = (uint32_t)MotorLeft.getPeriod() * 0.1;
        startPulsweite = pulsweite;
        deltaPulsweite = (uint32_t)MotorLeft.getPeriod() * 0.01;
        superviseOdometry = true;
        MotorLeft.setDutyCycle(pulsweite);
        MotorRight.setDutyCycle(pulsweite);
        MotorRight.MotorStart();
        MotorLeft.MotorStart();
        
       
        while (pulsweite <= endPulsweite && drivedDistance < _distance/2)
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        pulsweite += deltaPulsweite;
                        MotorRight.setDutyCycle(pulsweite); 
                        MotorLeft.setDutyCycle(pulsweite);
                        drivedDistance =  (distanceLeft + distanceRight) / 2;     
                }

        }
            
        alreadyDrived = drivedDistance;
        //std::cout << "Gefahrene Distanz: " << drivedDistance << std::endl;

  
        while (drivedDistance < (_distance - alreadyDrived))
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        drivedDistance =  (distanceLeft + distanceRight) / 2;
                }
        }
                    

        while(drivedDistance < _distance && pulsweite >= startPulsweite)
        {
                if(updateLeftOdometry == true && updateRightOdometry == true)
                {
                        updateLeftOdometry = false;
                        updateRightOdometry = false;
                        drivedDistance =  (distanceLeft + distanceRight) / 2;
                        pulsweite -= deltaPulsweite;
                        MotorRight.setDutyCycle(pulsweite); 
                        MotorLeft.setDutyCycle(pulsweite);                    
                }
        }

        MotorLeft.MotorStop();
        MotorRight.MotorStop();
        //std::cout << "In ECU -> gefahrene Distanz rechts: "<<distanceRight << "Gefahrene Distanz Links "<< distanceLeft << std::endl;

        return;
}
 
/****f* Ecu.h/controlMotorsCircula()
  *  NAME
  *    controlMotorsCircula() -- Regelt die Geschwindigkeiten der Motoren; Hier gibt es allerdings noch keine Be- und Entschleunigungsphase
  *  INPUTS
  *     _distanceToDriveLeft
  *     _distanceToDriveRight
  *     _speedLeft
  *     _speedRight
  *  RETURN VALUE
  *     NONE
  *  ERRORS
  *     Die Geschwindigkeiten sind noch nicht richtig berechnet. Das langsamer drehende Rad erreicht die übergebene Strecke nicht
  ******
  * 
  */
void Ecu::controlMotorsCircula(double _distanceToDriveLeft, double _distanceToDriveRight, uint8_t _speedLeft, uint8_t _speedRight)
{
        uint32_t pulsweiteLeft;
        uint32_t pulsweiteRight;
        double dummy;
        


        dummy = (double) _speedLeft/100 * MotorLeft.getPeriod();
        pulsweiteLeft = (uint32_t)dummy;
        dummy = (double)_speedRight/100 * MotorLeft.getPeriod();
        pulsweiteRight = (uint32_t)dummy;

        MotorLeft.setDutyCycle(pulsweiteLeft);
        MotorRight.setDutyCycle(pulsweiteRight);
        MotorLeft.MotorStart();
        MotorRight.MotorStart();




                        while (distanceLeft < _distanceToDriveLeft  && distanceRight < _distanceToDriveRight)
                        {
                                 if(updateRightOdometry == true && updateLeftOdometry == true)
                                {
                                updateLeftOdometry = false;
                                updateRightOdometry = false;
                                }

                        }
                       
         
             
        MotorLeft.MotorStop();
        MotorRight.MotorStop();

    return;
}
void Ecu::controlMotorsAngle2(double _distance)
{
        uint32_t pulsweite;
        double dummy;

        dummy = (double) 0.3 * MotorLeft.getPeriod();
        pulsweite = (uint32_t)dummy;

        MotorLeft.setDutyCycle(pulsweite);
        MotorRight.setDutyCycle(pulsweite);
        MotorLeft.MotorStart();
        MotorRight.MotorStart();
        double drivedDistance = 0;



                        while (drivedDistance < _distance)
                        {
                                 if(updateRightOdometry == true && updateLeftOdometry == true)
                                {
                                updateLeftOdometry = false;
                                updateRightOdometry = false;
                                }
                                drivedDistance =  (distanceLeft + distanceRight) / 2;
                        }
                       
              
        MotorLeft.MotorStop();
        MotorRight.MotorStop();

    return;
}
