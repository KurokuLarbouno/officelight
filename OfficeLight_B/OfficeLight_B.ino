#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_A0 = CapacitiveSensor(7, A0);
CapacitiveSensor cs_7_A1 = CapacitiveSensor(7, A1);
CapacitiveSensor cs_7_A2 = CapacitiveSensor(7, A2);
CapacitiveSensor cs_7_A3 = CapacitiveSensor(7, A3);
CapacitiveSensor cs_7_A4 = CapacitiveSensor(7, A4);
CapacitiveSensor cs_7_A5 = CapacitiveSensor(7, A5);
const int mainSensor = A5;
const int lt1 = 3, lt2 = 5, lt3 = 6, lt4 = 9, lt5 = 10, lt6 = 13;
int st1 = 0, st2 = 0, st3 = 0, st4 = 0, st5 = 0, st6 = 0;//st6是主燈
int sto = 0, stc = 0;
float curState = 0, brightness = 120;
unsigned long preTime = 0, postTime = 0;
int checktime = 200, sence = 1;
unsigned int trigger;
void setup() {
    Serial.begin(9600);
    pinMode(A1, INPUT); pinMode(A2, INPUT);pinMode(A3, INPUT);pinMode(A4, INPUT);pinMode(A5, INPUT);pinMode(mainSensor, INPUT);
    pinMode(lt1, OUTPUT);pinMode(lt2, OUTPUT);pinMode(lt3, OUTPUT);pinMode(lt4, OUTPUT);pinMode(lt5, OUTPUT);pinMode(lt6, OUTPUT);
    long cs = 0;
    for(int x = 0; x < 50; x++){
    cs += cs_7_A0.capacitiveSensor(30);
    cs += cs_7_A1.capacitiveSensor(30);
    cs += cs_7_A2.capacitiveSensor(30);
    cs += cs_7_A3.capacitiveSensor(30);
    cs += cs_7_A4.capacitiveSensor(30);
    Serial.println("/");
    }
    trigger = cs/250+300;
    Serial.print("trigger: ");
    Serial.println(trigger);
    delay(2000);
}

void loop() {
  // 更新sensor:
  switch(sence){
  case 1:
      st1 = (st1 ^ CSread(cs_7_A0)); sence = 2;/*Serial.println("1")*/; break;
  case 2:
      st2 = (st2 ^ CSread(cs_7_A1)); sence = 3; /*Serial.println("2")*/; break;
  case 3:
      st3 = (st3 ^ CSread(cs_7_A2)); sence = 4; /*Serial.println("3")*/; break;
  case 4:
      st4 = (st4 ^ CSread(cs_7_A3)); sence = 5; /*Serial.println("4")*/; break;
  case 5:
      st5 = (st5 ^ CSread(cs_7_A4)); sence = 6; /*Serial.println("5")*/; break;
  case 6:
      //st6 = (st6 ^ CSread(cs_7_A5)); sence = 1; /*Serial.println("6")*/; break;
      stc = digitalRead(2);
      if(!sto&&stc) st6 = st6 ^ 1;
      sto = stc;
      sence = 1; break;
  }
  if(st1|| st2 || st3 || st4 || st5 ){
        curState += (brightness - curState) * 0.015;
        if(curState >= 100) brightness = 0;
        if(curState <= 10)  brightness = 120;
  }
  digitalWrite(lt6, st6);
  analogWrite(lt1, curState * st1);
  analogWrite(lt2, curState * st2);
  analogWrite(lt3, curState * st3);
  analogWrite(lt4, curState * st4);
  analogWrite(lt5, curState * st5);
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

