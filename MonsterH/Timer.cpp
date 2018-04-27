#pragma once
//#include "Arduino.h"
//計算超過指定時間，回傳1
class Timer{
    public:
        unsigned long pass_time = 0, check_time = 0;
        Timer(){};
        unsigned long setTime(unsigned long time){
            pass_time = 0;
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
