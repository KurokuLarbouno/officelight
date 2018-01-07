#include <CapacitiveSensor.h>
CapacitiveSensor cs_7_A0 = CapacitiveSensor(7, A0);
long csSum1 = 0;
long c = 0;
unsigned long t = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(A1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  c++;
  long a; 
  a = cs_7_A0.capacitiveSensor(30);
//  Serial.print(a);
//  Serial.print("||");
  csSum1 += a;
  Serial.println (csSum1/c);
  if((millis()-t) >= 200){csSum1 = csSum1/c; c = 1; t = millis();}
  delay(10);
}
