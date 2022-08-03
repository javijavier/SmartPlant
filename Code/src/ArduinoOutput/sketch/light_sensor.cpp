#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\light_sensor.cpp"

#include "light_sensor.h"
#include "analog_sensor.h"

LightSensor::LightSensor(int analogPin) : AnalogSensor("LightSensor", analogPin) {


};

LightSensor::~LightSensor(){


}

void LightSensor::updateValue(){
    
    this->setData(this->getRawValue());

}

float LightSensor::getData(){

    this->updateValue();
    return this->getValue();
}
