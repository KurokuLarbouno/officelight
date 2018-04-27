//#pragma once
#ifndef __LED_MATRIX__
#define __LED_MATRIX__
#include "LedControl.h" 
#include "Timer.cpp"
//#include "Arduino.h"
#endif
class LedMatrix{
    public:
        unsigned int IMAGES_LEN;
        uint64_t IMG;
        LedMatrix(){
            display.clearDisplay(0);
            display.shutdown(0,false);
            display.setIntensity(0,10);
            mat_timer.setTime(100);
            life_timer.setTime(1500);
        };
        Timer mat_timer, life_timer;
        LedControl display=LedControl(12,11,10,1);  
        //LedControl display=LedControl(14,15,16,1);  // pin 12 is connected to the MAX7219 pin 1
                                                    // pin 11 is connected to the CLK pin 13
                                                    // pin 10 is connected to LOAD pin 12
                                                    // 1 as we are only using 1 MAX7219
        unsigned short i = 9, j = 0;       // matix row/colum
        unsigned short anim_kind = 0;
        unsigned short image = 0;
        bool has_wrote = 0;
        void Update(unsigned long delta){
            if(!has_wrote){
                if(anim_kind == 0){                 //rolling
                    unsigned long x = mat_timer.tUpdate(delta);
                    if(x && i < 8){
                            byte row = (IMG >> i * 8) & 0xFF;
                            for(int j = 0; j < 8; j++){
                                display.setLed(0, i, j, bitRead(row, j));
                            }
                            i++;
                    }else if(i >= 8){
                        has_wrote = 1;
                        life_timer.Reset();
                    }
                }
            }else{
                unsigned long x = life_timer.tUpdate(delta);
                //if(x){display.clearDisplay(0);}
            }
            
        };
        void SetAnim(int index){
            if(index == 0) anim_kind = index;
        };
        void SetImg(uint64_t Mat){
            IMG = Mat;
            display.clearDisplay(0);
            i = 0; j = 0; has_wrote = 0;
            mat_timer.Reset();
        };
};
