/*--------------------------------------電容部分---------------------------------------*/
#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_A1 = CapacitiveSensor(53, A1);
CapacitiveSensor cs_7_A2 = CapacitiveSensor(53, A2);
CapacitiveSensor cs_7_A3 = CapacitiveSensor(53, A3);
CapacitiveSensor cs_7_A4 = CapacitiveSensor(53, A4);
CapacitiveSensor cs_7_A5 = CapacitiveSensor(53, A5);
CapacitiveSensor cs_7_A6 = CapacitiveSensor(53, A6);
const int lt1 = 2, lt2 = 3, lt3 = 4, lt4 = 5, lt5 = 6, lt6 = 7;
int st1 = 0, st2 = 0, st3 = 0, st4 = 0, st5 = 0, st6 = 0; //st6是主燈
float curState = 0, brightness = 120;
int sence = 1;
unsigned int trigger;
/*--------------------------------------壓感部分---------------------------------------*/
unsigned int avrg = 0;
unsigned long pretime = 0, posttime = 0, plateposttime = 0;
const int mainSensor = A7, mainlt = 8, TIME_TO_TRIGGER = 10;
int loadcount = 0, empcount = 0, mainst= 0;//負重/空盤判定
float platebr = 255;
void setup() {
    Serial.begin(9600);
    pinMode(A1, INPUT); pinMode(A2, INPUT);pinMode(A3, INPUT);pinMode(A4, INPUT);pinMode(A5, INPUT);pinMode(A6, INPUT);pinMode(mainSensor, INPUT);
    pinMode(lt1, OUTPUT);pinMode(lt2, OUTPUT);pinMode(lt3, OUTPUT);pinMode(lt4, OUTPUT);pinMode(lt5, OUTPUT);pinMode(lt6, OUTPUT);
    long cs = 0;
    unsigned int sum = 0;
    for(int x = 0; x < 50; x++){
    cs += cs_7_A1.capacitiveSensor(30);
    cs += cs_7_A2.capacitiveSensor(30);
    cs += cs_7_A3.capacitiveSensor(30);
    cs += cs_7_A4.capacitiveSensor(30);
    cs += cs_7_A5.capacitiveSensor(30);
    cs += cs_7_A6.capacitiveSensor(30);
    sum += analogRead(mainSensor);
    Serial.println("/");
    }
    avrg = sum/50; Serial.print("環境值: "); Serial.println(avrg);
    trigger = cs/300+300; Serial.print("trigger: "); Serial.println(trigger);
}

void loop() {
  /*--------------------------------------電容部分---------------------------------------*/
  // 更新sensor:
  switch(sence){
  case 1:
      st1 = (st1 ^ CSread(cs_7_A1)); sence = 2;/*Serial.println("1")*/; break;
  case 2:
      st2 = (st2 ^ CSread(cs_7_A2)); sence = 3; /*Serial.println("2")*/; break;
  case 3:
      st3 = (st3 ^ CSread(cs_7_A3)); sence = 4; /*Serial.println("3")*/; break;
  case 4:
      st4 = (st4 ^ CSread(cs_7_A4)); sence = 5; /*Serial.println("4")*/; break;
  case 5:
      st5 = (st5 ^ CSread(cs_7_A5)); sence = 6; /*Serial.println("5")*/; break;
  case 6:
      st6 = (st6 ^ CSread(cs_7_A6)); sence = 1; /*Serial.println("6")*/; break;
  }
  /*--------------------------------------壓感部分---------------------------------------*/
  int ang = analogRead(mainSensor);
  //Serial.println(ang);
  if( ang > avrg+15){ pretime = millis(); loadcount++; }
  if(ang < avrg+5){ pretime = millis(); empcount++; }
  if((pretime-posttime)>=150){
    if (loadcount >= TIME_TO_TRIGGER) { mainst = 1; }
    if (empcount >= TIME_TO_TRIGGER) { mainst = 0; }
    loadcount = 0;  empcount = 0;  posttime = pretime;
  }
  if(mainst == 1){
//    Serial.print( millis()); Serial.print( "  "); Serial.println( plateposttime);
    if((millis()-plateposttime) >= 5000){
      platebr += (10 - platebr) * 0.015;
      if(platebr<12) plateposttime = millis();
    }
    analogWrite(mainlt, platebr);
  }else{
    plateposttime = millis();
    analogWrite(mainlt, 0);
    platebr = 255;
  }
  
  if(st1|| st2 || st3 || st4 || st5 || st6){
        curState += (brightness - curState) * 0.015;
        if(curState >= 100) brightness = 0;
        if(curState <= 10)  brightness = 120;
  }
  analogWrite(lt1, curState * st1);
  analogWrite(lt2, curState * st2);
  analogWrite(lt3, curState * st3);
  analogWrite(lt4, curState * st4);
  analogWrite(lt5, curState * st5);
  analogWrite(lt6, curState * st6);
}
bool CSread(CapacitiveSensor &capaSence) {
  long cs = capaSence.capacitiveSensor(30); //a: Sensor resolution is set to 80
  if (cs>= trigger) //c: This value is the threshold, a High value means it takes longer to trigger
  {
      capaSence.reset_CS_AutoCal(); //Stops readings
      return(1);
  }
  return(0);
}

