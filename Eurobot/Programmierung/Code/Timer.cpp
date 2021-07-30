#include "Timer.h"



Timer::Timer(){}


/****f* Timer.h/startTimer()
  *  NAME
  *    startTimer() -- Starten des Timers 
  *  INPUTS
  *     NONE
  *  RETURN VALUE
  *     NONE
  ******
  * 
*/
void Timer::startTimer()
{
    start_t = clock();
}



/****f* Timer.h/getTime()
  *  NAME
  *    getTime() -- Zeit wird 
  *  INPUTS
  *     _edge - Value which overrides the attribute edge
  *  RETURN VALUE
  *     just 0
  *  NOTES
  *    getTime() stoppt nicht den Timer sondern berechnet nur die zeitliche Differenz von Start bis zum Aufruf der Methode.
  *    Würde man aus irgend einen Grund diese Zeit nochmals benötigen, wird diese nach aufruf von getTimer in time gespeichert
  *    -> Diese ist dann solange vorhanden, bis startTimer() aufgerufen wird
  ******
  * 
*/
double Timer::getTime(TimerOption _unit)
{   
    TimerOption unit = _unit;
    clock_t diff;
    double time_unit;

    if(start_t==0)
    {
        std::cout << "Es wurde kein Timer gesetzt!" <<   std::endl;
    }
    else
    {
        end_t = clock();
        diff = end_t - start_t;
        time = (double) diff / CLOCKS_PER_SEC;

             switch(unit)
        {
            case sec: break;   
            case msec:  time_unit = time * pow(10,3);
                        time =  time_unit; break; 
            case usec: time_unit = time * pow(10,6);
                        time =  time_unit; break; 
            case nsec: time_unit = time * pow(10,9);
                        time =  time_unit; break; 
            default: std::cout << "TIMER_UNIT_ERROR" << std::endl; break;
        }
    }
    return time;
    
}
