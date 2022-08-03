// moisture_sensor_h

//This is the moisture sensor class derived from the analog_sensor BaseClass

#ifndef moisture_sensor_h
#define moisture_sensor_h

#include <Arduino.h>
#include "analog_sensor.h"

class MoistureSensor : public AnalogSensor {

    private:

        void updateValue();
    public:
        MoistureSensor(int analogPin);
        ~MoistureSensor();

        float getData();
        
};

#endif
