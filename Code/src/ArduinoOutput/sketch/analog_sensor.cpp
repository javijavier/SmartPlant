#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\analog_sensor.cpp"
// analog_sensor.h

#include "analog_sensor.h"

AnalogSensor::AnalogSensor(char *deviceName, int analogPin){

    this->m_cDeviceName = deviceName;
    this->m_iPin = analogPin;
    float m_fRawValue = 0.0;
    float m_fValue = 0.0;

}

char *AnalogSensor::getDeviceName(){

    return this->m_cDeviceName;

}

int AnalogSensor::getPin(){

    return this->m_iPin;
}

float AnalogSensor::getValue(){

    return this->m_fValue;
}

float AnalogSensor::getRawValue(){

    this->updateRawValue();
    return this->m_fRawValue;
}

void AnalogSensor::setDeviceName(char *deviceName){

    this->m_cDeviceName = deviceName;
}

void AnalogSensor::setPin(int pin){

    this->m_iPin = pin;
}
void AnalogSensor::setRawData(float value){

    this->m_fRawValue = value;
}

void AnalogSensor::setData(float value){

    this->m_fValue = value;
}

void AnalogSensor::updateRawValue(){

    this->m_fRawValue = analogRead(this->m_iPin);
}


void AnalogSensor::print(float value){

    Serial.print(this->getDeviceName());
    Serial.print(": ");
    Serial.print(value);
    Serial.print("\n-------------------------------------------\n");
}


void AnalogSensor::printRawData(){
    this->updateRawValue();
    Serial.print("\n-------------------RAW DATA--------------------\n");
    this->print(this->getRawValue());
}

void AnalogSensor::printData(){
    this->updateValue();
    Serial.print("\n---------------------DATA----------------------\n");
    this->print(this->getValue());
}


