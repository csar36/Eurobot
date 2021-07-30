#include "stdafx.h"
#include "Ecu.h"





int main(int argc, char** argv)
{

   
    double angle, strecke, radius;
    Ecu Controller;
    uint8_t speed;
    std::string option = argv[1];
    std::string directionOfRotation, direction;
    //****//INITIALISIERUNGSPHASE//****//
    Controller.configRegulatorRight(ANALOG_INPUT_4);
    Controller.configRegulatorLeft(ANALOG_INPUT_5);
    Controller.configMotorRight(GPIO_27, GPIO_47, P8_19,  2000000);
    Controller.configMotorLeft(GPIO_45, GPIO_69, P8_13,  2000000);
    Controller.configInfraredSensors(ANALOG_INPUT_2, ANALOG_INPUT_0, ANALOG_INPUT_1, ANALOG_INPUT_3);

    Controller.ServoMotor.setPin(P9_14);
    Controller.ServoMotor.setPeriod(20000000);
    Controller.ServoMotor.setMinDutyCycle(550000);
    Controller.ServoMotor.setMaxDutyCycle(2450000);
    //*********************************************//
   
    if(option == "-export")
    {   
        Controller.MotorRight.exportPWM(P8_19);
        Controller.MotorLeft.exportPWM(P8_13);
        Controller.ServoMotor.exportPWM(P9_14);
        std::cout << "PWMChips erfolgreich exportiert!" << std::endl;
        return 0;
    }
    else if(option == "-forward")
    {
        strecke = atof(argv[2]);
        speed = atoi(argv[3]); 
      
        Controller.driveForward(strecke,speed);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 0;
    }
      else if(option == "-backward")
    {
        strecke = atof(argv[2]);
        speed = atoi(argv[3]); 
      
        Controller.driveBackward(strecke,speed);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 0;
    }
    else if(option == "-angle")
    {   
        directionOfRotation = argv[2];
        angle = atof(argv[3]);
        Controller.driveAngle(angle, directionOfRotation);

    }
    else if(option == "-circula")     //Eingabebeispiel: ./Robot -circula -forward -cw 50[cm]->radius 360->angle 60->speed
    {  
        direction = argv[2];
        directionOfRotation = argv[3];
        radius = atof(argv[4]);
        angle = atof(argv[5]);
        Controller.driveCircula(radius, angle, direction, directionOfRotation);
    }
    else if(option == "-servo")
    {
    Controller.ServoMotor.setPin(P9_14);
    Controller.ServoMotor.setPeriod(20000000);
    Controller.ServoMotor.setMinDutyCycle(550000);
    Controller.ServoMotor.setMaxDutyCycle(2450000);
    Controller.ServoMotor.setWinkel(120); 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Controller.ServoMotor.setWinkel(30); 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Controller.ServoMotor.setWinkel(90); 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Controller.ServoMotor.setWinkel(160); 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Controller.ServoMotor.setWinkel(0); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Controller.ServoMotor.setWinkel(180); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
     Controller.ServoMotor.setWinkel(0); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Controller.ServoMotor.setWinkel(180); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
     Controller.ServoMotor.setWinkel(0); 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    Controller.ServoMotor.setWinkel(180); 
    }
    else if(option =="-example")
    {

        Controller.driveForward(170,50);
        Controller.driveAngle(90, "-cw");

        Controller.ServoMotor.setWinkel(0);
        Controller.ServoMotor.setWinkel(180); 
        Controller.ServoMotor.setWinkel(0); 
        Controller.driveForward(150,80);
        //Controller.driveAngle(360, "-cw");
        //Controller.driveAngle(180, "-cw");
        Controller.driveBackward(150,80);
       //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Controller.driveAngle(90, "-ccw");
        Controller.driveBackward(170,80);
        Controller.ServoMotor.setWinkel(180);
    }


  
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}
