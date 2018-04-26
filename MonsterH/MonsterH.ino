//#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__
    #include <CapacitiveSensor.h>
    #include "LedControl.h" 
    #include "LedStrip.cpp" 
    #include "Timer.cpp"
    #include "LedMarix.cpp"
#endif
        uint64_t IMAGES[115] = {
            0x0008080808080c08,
            0x003e04081020221c,
            0x001c22201008103e,
            0x0010103e12141810,
            0x001c2220201e023e,
            0x001c22221e020418,
            0x000404040810203e,
            0x001c22221c22221c,
            0x000c10203c22221c,
            0x00728a9aaaca8b72,
            0x0022222222223322,
            0x00fa122242828b72,
            0x00728a82422243fa,
            0x004242fa4a526342,
            0x00728a82827a0bfa,
            0x00728a8a7a0a1362,
            0x00121212224283fa,
            0x00728a8a728a8b72,
            0x00324282f28a8b72,
            0x006f919294989966,
            0x004f414244486946,
            0x00ff112244889966,
            0x006f9182442849f6,
            0x004f41f254586946,
            0x006f9182741819f6,
            0x006f919274182946,
            0x002f2122244889f6,
            0x006f919264989966,
            0x006f8182e4989966,
            0x006699989492946f,
            0x004649484442644f,
            0x00f619284482946f,
            0x00668988442244ff,
            0x004649f85452644f,
            0x00669988847214ff,
            0x006699987412244f,
            0x00262928244284ff,
            0x006699986492946f,
            0x00668988e492946f,
            0x0064949f95959664,
            0x0044444f45456644,
            0x00f4142f45859664,
            0x0064948f452546f4,
            0x004444ff55556644,
            0x0064948f857516f4,
            0x0064949f75152644,
            0x0024242f254586f4,
            0x0064949f65959664,
            0x0064848fe5959664,
            0x006699989897916f,
            0x004649484847614f,
            0x00f619284887916f,
            0x00669988482741ff,
            0x004649f85857614f,
            0x00669988887711ff,
            0x006699987817214f,
            0x00262928284781ff,
            0x006699986897916f,
            0x00668988e897916f,
            0x0066999997919264,
            0x0046494947416244,
            0x00f6192947819264,
            0x00669989472142f4,
            0x004649f957516244,
            0x00669989877112f4,
            0x0066999977112244,
            0x00262929274182f4,
            0x0066999967919264,
            0x00668989e7919264,
            0x006292929294986f,
            0x004242424244684f,
            0x00f212224284986f,
            0x00629282422448ff,
            0x004242f25254684f,
            0x00629282827418ff,
            0x006292927214284f,
            0x00222222224488ff,
            0x006292926294986f,
            0x00628282e294986f,
            0x0066999996999966,
            0x0046494946496946,
            0x00f6192946899966,
            0x00669989462949f6,
            0x004649f956596946,
            0x00669989867919f6,
            0x0066999976192946,
            0x00262929264989f6,
            0x0066999966999966,
            0x00668989e6999966,
            0x006698989e999966,
            0x004648484e496946,
            0x00f618284e899966,
            0x006698884e2949f6,
            0x004648f85e596946,
            0x006698888e7919f6,
            0x006698987e192946,
            0x002628282e4989f6,
            0x006698986e999966,
            0x00668888ee999966,
            0x00324a4a4a4a4b32,
            0x0019a5a5a5a5a519,
            0x008c52525252528c,
            0x00c62929292929c6,
            0x0063949494949463,
            0x00314a4a4a4a4a31,
            0x0018252525252518,
            0x000c12121212120c,
            0x0006090909090906,
            0x0003040404040403,
            0x0001020202028201,
            0x008081818181c180,
            0x0040404040406040,
            0x0090505050505890,
            0x00c8282828282cc8,
            0x0064949494949664
        };

//promicro pwm:3,5,6,9,10 Analog read:4,6,8,9,10,18,19,20,21 digital:2,3,5,7
//腳位宣告區
    //LED matix
        //LedControl display=LedControl(12,11,10,1);
        //LedControl display=LedControl(14,15,16,1);  // pin 12 is connected to the MAX7219 pin 1
                                                    // pin 11 is connected to the CLK pin 13
                                                    // pin 10 is connected to LOAD pin 12
                                                    // 1 as we are only using 1 MAX7219
//變數宣告區
    //IR
        const short IR_pin = 2;      // 紅外線接收-器
    //capa
        CapacitiveSensor* cs1; CapacitiveSensor* cs2;
        CapacitiveSensor* cs3; CapacitiveSensor* cs4;
        const short lt1 = 3, lt2 = 5, lt3 = 6, lt4 = 9;                                //狀態顯示燈
        unsigned int csSum1 = 0, csSum2 = 0, csSum3 = 0, csSum4 = 0, csSum5 = 0;       //電容觸控門檻
        short st1 = 0, st2 = 0, st3 = 0, st4 = 0, st5 = 0;
        float curState = 0, brightness = 120;
        int sence = 1;//現在檢查位置
        unsigned int trigger;
        Timer capa_timer;
    //IR
        bool IR_new_status = false, IR_old_status = false, goaling = false, IR_cd = false;
        Timer IR_timer;
    //LED matix
        LedMatrix myMax;
        Timer mat_timer;
    //LED strip
        LedStrip myStp;
        Timer stp_timer;    
    //animation
        unsigned long preTime = 0, post_time = 0, delta_time = 0;
        unsigned int score = 0;

void setup() {
    Serial.begin(9600);
    //capa
        cs1 = new CapacitiveSensor(7, A0); cs2 = new CapacitiveSensor(7, A1);
        cs3 = new CapacitiveSensor(7, A2); cs4 = new CapacitiveSensor(7, A3);
        pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); pinMode(A3, INPUT);
        pinMode(3, OUTPUT); pinMode(5, OUTPUT); pinMode(6, OUTPUT);  pinMode(9, OUTPUT);
        // unsigned int cs;
        // for(int x = 0; x < 50; x++){
        //     cs += cs1.capacitiveSensor(30); cs += cs2.capacitiveSensor(30); cs += cs3.capacitiveSensor(30); cs += cs4.capacitiveSensor(30);
        //     Serial.println("/");}
        // trigger = cs/200+300; Serial.print("trigger: "); Serial.println(trigger);
    //matrix
        //display.clearDisplay(0);
        //display.shutdown(0,false);
        //display.setIntensity(0,10);
        myMax.SetImg(IMAGES[0]);
        myStp.SetUp();
        myStp.Emmit();
    capa_timer.setTime(500);
    IR_timer.setTime(500);
    mat_timer.setTime(500);
    IR_timer;
    mat_timer;
    preTime = millis();
    post_time = preTime;
}
void loop() {
    preTime = millis();
    delta_time = preTime - post_time;
    post_time = preTime;
    // Serial.print("DT: "); Serial.println(delta_time);
/*-----------------------------偵測-----------------------------*/
    //電容感應
        // capaRead(delta_time);
    //IR感應
        IRRead();
        if (IR_cd){
            goaling = false;
            if(IR_timer.tUpdate(delta_time)){IR_cd = 0; IR_timer.Reset();}
        }else if (goaling) {
            goaling = false;
            IR_cd = true;
            if(score<100)score++;else score = 0;
            goal();
        }
/*-----------------------------顯示-----------------------------*/
        myMax.Update(delta_time);
        myStp.sUpdate(delta_time);
}
void capaRead(unsigned short delta){
    switch(sence){
        case 1:
            st1 = (st1 ^ CSread(*cs1)); sence = 2;/*Serial.println("1")*/; break;
        case 2:
            st2 = (st2 ^ CSread(*cs2)); sence = 3; /*Serial.println("2")*/; break;
        case 3:
            st3 = (st3 ^ CSread(*cs3)); sence = 4; /*Serial.println("3")*/; break;
        case 4:
            st4 = (st4 ^ CSread(*cs4)); sence = 5; /*Serial.println("4")*/; break;
        case 5:
            //if(capa_timer->Update(delta_time)){capa_timer->Reset();sence = 1;} 
            break;
        }
}
bool CSread(CapacitiveSensor &capaSence) {
  short cs = capaSence.capacitiveSensor(30); //a: Sensor resolution is set to 80
  if (cs>= trigger) //c: This value is the threshold, a High value means it takes longer to trigger
  {
      capaSence.reset_CS_AutoCal(); //Stops readings
      return(1);
  }
  return(0);
}
void IRRead(){
    IR_new_status = digitalRead(2);
    if(IR_old_status == 1 && IR_new_status == 0){goaling = 1;}
    IR_old_status = IR_new_status;

}
void goal(){
    //LED 燈條動畫
    myMax.SetImg(IMAGES[score]);
    //LED 陣列動畫
    myStp.Emmit();
}
// void displayImage(uint64_t image){
//     for(int i = 0; i < 8; i++){
//         byte row = (image >> i * 8) & 0xFF;
//         for(int j = 0; j < 8; j++){
//             display.setLed(0, i, j, bitRead(row, j));
//         }
//     }
//}
