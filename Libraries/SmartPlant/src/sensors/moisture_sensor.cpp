
#include "moisture_sensor.h"
#include "analog_sensor.h"

MoistureSensor::MoistureSensor(int analogPin) : AnalogSensor("MoistureSensor", analogPin) {


};

MoistureSensor::~MoistureSensor(){


}

void MoistureSensor::updateValue(){
    
    this->setData(this->getRawValue());

}

float MoistureSensor::getData(){

    this->updateValue();
    return this->getValue();
}
