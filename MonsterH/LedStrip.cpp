#include <Adafruit_NeoPixel.h>
//#pragma once
#ifndef __LED_STRIP__
#define __LED_STRIP__
  #include "Timer.cpp" 
  #include "Arduino.h"
#endif

class LedStrip{
    public:
    unsigned short PIN = 6;
    unsigned int pixel_num = 60, i = 0;
    uint32_t color,black, wait_time;
    uint16_t strip_index;
    Adafruit_NeoPixel* strip; 
    Timer stp_timer;
    unsigned short anim_kind = 0;
    bool has_wrote = 0;
    LedStrip(){
      stp_timer.setTime(10);
    };
    SetUp(){
      strip = new Adafruit_NeoPixel(pixel_num, PIN, NEO_GRB + NEO_KHZ800);
      //Serial.println(strip->canShow());//判斷功能運作狀況
      strip->begin();
      strip->show();
      color = strip->Color(127, 0, 127);black = strip->Color(0, 0, 0);
      strip->show();
    }
    void sUpdate(unsigned long delta){
      if(!has_wrote){
        if(anim_kind == 0){                 //rolling
          unsigned long x = stp_timer.tUpdate(delta);
          if(x && i < pixel_num){
            strip->setPixelColor(i, color);
            strip->show();
            i++;
          }else if(i >= pixel_num && i < 2 * pixel_num){
            if(x && i - pixel_num <pixel_num){
              strip->setPixelColor(i - pixel_num, black);
              strip->show();
              i++;
            }
          }else if(i >= 2 * pixel_num){
            has_wrote = 1;
            i = 0;
          }
        }
      }
            
    };
    void SetAnim(int index){
      if(index == 0) anim_kind = index;
    };
    void Emmit(){
      if(i>pixel_num*2) i = 0;has_wrote = 0;
    };
};
