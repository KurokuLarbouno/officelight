#pragma once
//#include "Arduino.h"
class Timer{
    public:
        unsigned long pass_time = 0, check_time = 11155;
        Timer(){};
        unsigned long setTime(unsigned long time){
            check_time = time;
        }
        bool tUpdate(unsigned long delta){
            pass_time += delta;
            if(pass_time >= check_time){pass_time = 0; return(1);}
            else return(0);
        }
        void Reset(){
            pass_time = 0;
        }
};
