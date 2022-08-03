# 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
// main code: main.code

# 4 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino" 2
# 5 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino" 2

TemperatureSensor TempSensor(A2);

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
