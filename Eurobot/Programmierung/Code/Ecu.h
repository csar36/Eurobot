#include "stdafx.h"
#include "Motor.h"
#include "Odometry.h"
#include "gpio.h"
#include "InfraredSensor.h"
#include "Servo.h"

/****c* Ecu.h/Ecu
  *  NAME
  *    InfraredSensor -- 
  *  DESCRIPTION
  *    
  *  METHODS 
  *      configMotorRight()
  *      configMotorLeft()
  *      configRegulatorRight()
  *      configRegulatorLeft()                         
  *      configInfraredSensors()
  *      driveForward()                                           
  *      driveBackward() 
  *      driveAngle()
  *      driveCircula()
  *      controlMotorsStraight()
  *      controlMotorsAngle();
  *      controlMotorsCircula()
  *  ATTRIBUTES
  *      MotorRight
  *      MotorLeft
  *      ServoMotor
  *
  *      RegulatorLeft              
  *      RegulatorRight
  * 
  *      InfraredSensor_FrontLeft
  *      InfraredSensor_FrontRight
  *      InfraredSensor_BackLeft
  *      InfraredSensor_BackRight
  *
  *      wheelSpace                     
  *      PI
  *     
  *      superviseInfrared              -- wird benötigt um InfrarotSensor Threads zu beenden
  *      p_superviseInfrared            -- Übergabe an Thread; call by reference
  *      
  *      StateInfraredSensor_FrontLeft  -- States der einzelnen Infrarotsensor, diese teilen Funktionen zum steuern der Motoren mit, ob Motor entschleunigen oder anhalten soll
  *      StateInfraredSensor_FrontRight 
  *      StateInfraredSensor_BackLeft 
  *      StateInfraredSensor_BackRight 
  *      p_StateInfraredSensor_FrontLeft 
  *      p_StateInfraredSensor_FrontRight 
  *      p_StateInfraredSensor_BackLeft 
  *      p_StateInfraredSensor_BackRight 
  *
  *      distanceLeft                    -- gefahrene Distanz 
  *      distanceRight
  *      p_distanceRight                 -- Übergabe an Thread für Odometry; call by reference
  *      p_distanceLeft 
  *      
  *      updateLeftOdometry             -- Teilt der Funktion zum kontrollieren der Motoren mit, wann gefahrene Distanz aktualisiert wurde
  *      updateRightOdometry
  *      superviseOdometry              -- wird benötigt um Threads zu beenden
  *      p_updateRightOdometry 
  *      p_updateLeftOdometry
  *      p_superviseOdometry                    
  *  NOTES
  *
  ******
  * 
*/ 
class Ecu
{       
        
public:
        Ecu();
        Ecu(MOTOR, MOTOR);
        ~Ecu();
        
        MOTOR MotorRight;
        MOTOR MotorLeft;
        Servo ServoMotor;

        Odometry RegulatorLeft;
        Odometry RegulatorRight;

        InfraredSensor InfraredSensor_FrontLeft;
        InfraredSensor InfraredSensor_FrontRight;
        InfraredSensor InfraredSensor_BackLeft;
        InfraredSensor InfraredSensor_BackRight;

        double wheelSpace = 25.179;
        const double PI = 3.14159265359;
       
        bool superviseInfrared;
        bool* p_superviseInfrared = &superviseInfrared;
        
        volatile uint8_t StateInfraredSensor_FrontLeft = 0;
        volatile uint8_t StateInfraredSensor_FrontRight = 0;
        volatile uint8_t StateInfraredSensor_BackLeft = 0;
        volatile uint8_t StateInfraredSensor_BackRight = 0;
        volatile uint8_t* p_StateInfraredSensor_FrontLeft = &StateInfraredSensor_FrontLeft;
        volatile uint8_t* p_StateInfraredSensor_FrontRight = &StateInfraredSensor_FrontRight;
        volatile uint8_t* p_StateInfraredSensor_BackLeft = &StateInfraredSensor_BackLeft;
        volatile uint8_t* p_StateInfraredSensor_BackRight = &StateInfraredSensor_BackRight;

        volatile double distanceLeft = 0;
        volatile double distanceRight = 0;
        volatile double* p_distanceRight = &distanceRight;
        volatile double* p_distanceLeft = &distanceLeft;
        
        volatile bool updateLeftOdometry = false;
        volatile bool updateRightOdometry = false;
        volatile bool superviseOdometry = false;
        volatile bool* p_updateRightOdometry = &updateRightOdometry;
        volatile bool* p_updateLeftOdometry = &updateLeftOdometry;
        volatile bool* p_superviseOdometry = &superviseOdometry;
      

        
        void configMotorRight(GPIOPin _enablePin, GPIOPin _directionPin, PWMPin _pwmpin, uint32_t _period);
        void configMotorLeft(GPIOPin _enablePin, GPIOPin _directionPin, PWMPin _pwmpin, uint32_t _period);
        void configRegulatorRight(AnalogInputChannel _channel);
        void configRegulatorLeft(AnalogInputChannel _channel);                         
        void configInfraredSensors(AnalogInputChannel _FrontLeft, AnalogInputChannel _FrontRight, AnalogInputChannel _BackLeft, AnalogInputChannel _BackRight);
        void driveForward(double _distance, uint8_t _speed);                                            
        void driveBackward(double _distance, uint8_t _speed); 
        void driveAngle(double _angle, std::string _directionOfRotation); 
        void driveCircula(double _radius, double _angle, std::string _direction, std::string _directionOfRotation);
        void controlMotorsStraight(double _distance, uint8_t _speed, volatile uint8_t* _p_InfraredLeft, volatile uint8_t* _p_InfraredRight);
        void controlMotorsAngle(double _distance);
        void controlMotorsCircula(double _distanceToDriveLeft, double _distanceToDriveRight, uint8_t _speedLeft, uint8_t _speedRight);  
        void controlMotorsAngle2(double _distance);    
};
