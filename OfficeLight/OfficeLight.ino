#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_A0 = CapacitiveSensor(7, A0);
CapacitiveSensor cs_7_A1 = CapacitiveSensor(7, A1);
CapacitiveSensor cs_7_A2 = CapacitiveSensor(7, A2);
CapacitiveSensor cs_7_A3 = CapacitiveSensor(7, A3);
CapacitiveSensor cs_7_A4 = CapacitiveSensor(7, A4);
unsigned long csSum1 = 0, csSum2 = 0, csSum3 = 0, csSum4 = 0, csSum5 = 0;
const int mainSensor = A5;
const int lt1 = 3, lt2 = 5, lt3 = 6, lt4 = 9, lt5 = 10, mainLt = 13;
int st1 = 0, st2 = 0, st3 = 0, st4 = 0, st5 = 0, mainState = 0;
float curState = 0, brightness = 120;
unsigned long preTime = 0, postTime = 0;
int checktime = 200, sence = 1;
void setup() {
    Serial.begin(9600);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(mainSensor, INPUT);
    pinMode(lt1, OUTPUT);
    pinMode(lt2, OUTPUT);
    pinMode(lt3, OUTPUT);
    pinMode(lt4, OUTPUT);
    pinMode(lt5, OUTPUT);
    pinMode(mainLt, OUTPUT);
}

void loop() {
  preTime = millis();
  mainState = digitalRead(mainSensor);
  // 更新sensor:
  switch(sence){
  case 1:
      if(!st1){st1 = (st1 || CSread(cs_7_A0));} sence = 2; Serial.println("1"); break;
  case 2:
      if(!st2){st2 = (st2 || CSread(cs_7_A1));} sence = 3; Serial.println("2"); break;
  case 3:
      if(!st3){st3 = (st3 || CSread(cs_7_A2));} sence = 4; Serial.println("3"); break;
  case 4:
      if(!st4){st4 = (st4 || CSread(cs_7_A3));} sence = 5; Serial.println("4"); break;
  case 5:
      if(!st5){st5 = (st5 || CSread(cs_7_A4));} sence = 1; Serial.println("5"); break;
  }
//  Serial.print("ST: ");
//  Serial.print(st1);
//  Serial.print(st2);
//  Serial.print(st3);
//  Serial.print(st4);
//  Serial.println(st5);
  digitalWrite(mainLt, mainState);
  if(mainState){//繼電器開，st重設
    st1 = 0; st2 = 0; st3 = 0; st4 = 0; st5 = 0;
    curState = 0;
    analogWrite(lt1, 0);
    analogWrite(lt2, 0);
    analogWrite(lt3, 0);
    analogWrite(lt4, 0);
    analogWrite(lt5, 0);
  }else{
    if(st1|| st2 || st3 || st4 || st5){
        curState += (brightness - curState) * 0.015;
        if(curState >= 100) brightness = 0;
        if(curState <= 10)  brightness = 120;
    }
    if(st1) analogWrite(lt1, curState);
    if(st2) analogWrite(lt2, curState);
    if(st3) analogWrite(lt3, curState);
    if(st4) analogWrite(lt4, curState);
    if(st5) analogWrite(lt5, curState);
  }
  
}
bool CSread(CapacitiveSensor &capaSence) {
  long cs = capaSence.capacitiveSensor(10); //a: Sensor resolution is set to 80
  if (cs>= 300) //c: This value is the threshold, a High value means it takes longer to trigger
  {
      capaSence.reset_CS_AutoCal(); //Stops readings
      return(1);
  }
  return(0);
}

