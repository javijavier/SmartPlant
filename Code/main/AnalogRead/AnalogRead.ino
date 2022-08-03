/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13 through 220 ohm resistor
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

int lightPin = A0;    // select the input pin for the potentiometer
int lightValue = 0;  // variable to store the value coming from the sensor

int moisturePin = A1;    // select the input pin for the potentiometer
int moistureValue = 0;  // variable to store the value coming from the sensor

int tempPin = A2;    // select the input pin for the potentiometer
int tempValue = 0;  // variable to store the value coming from the sensor

int B=3975;
float temperature;
float resistance;

void setup() {
  Serial.begin(9600);
}0

void loop() {
  // read the value from the sensor:
  lightValue = analogRead(lightPin);            // <500 Poquita luz >500 Luz!
  
  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print('\n');

  moistureValue = analogRead(moisturePin);      //0 < 300 Seco, 300 < 600 Humedo, >600 Mojado
  
  Serial.print("Moisture: ");
  Serial.print(moistureValue);          
  Serial.print('\n');

  tempValue = analogRead(tempPin);
  resistance=(float)(1023-tempValue)*10000/tempValue; 
  temperature= 1/(log(resistance/10000)/B+1/298.15)-273.15;   
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print('\n');

  Serial.print("---------------------------------");
  Serial.print('\n');

  delay(2000);

}
