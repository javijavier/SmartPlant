#include <Arduino.h>
#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
// main code: main.code

#include <iostream>
#include "temperature_sensor.h"

TemperatureSensor TempSensor(A2);

#line 8 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
void setup();
#line 14 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
void loop();
#line 8 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
void setup() {
  Serial.print("Init module!");

  Serial.begin(9600);
}

void loop() {

  float rawData = TempSensor.getData();
  Serial.print("rawData: " + String(rawData));
  float data = TempSensor.getData();
  Serial.print("Data: " + String(data));
  delay(1000);
  
}

