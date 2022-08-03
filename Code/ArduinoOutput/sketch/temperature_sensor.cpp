#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\temperature_sensor.cpp"

#include "temperature_sensor.h"
#include "analog_sensor.h"

TemperatureSensor::TemperatureSensor(int analogPin) : AnalogSensor("TemperatureSensor", analogPin) {

    this->m_iB = 3975;
    this->m_fResistance = 0.0;

};

TemperatureSensor::~TemperatureSensor(){


}

void TemperatureSensor::updateValue(){
    
    this->m_fResistance = (float)(1023 - this->getRawData())*10000/this->getRawData(); 
    this->setData(1/(log(this->m_fResistance/10000)/this->m_iB + 1/298.15)-273.15);

}

float TemperatureSensor::getData(){

    this->updateValue();
    return this->getData();
}
