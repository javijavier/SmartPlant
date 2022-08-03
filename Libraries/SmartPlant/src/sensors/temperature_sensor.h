// temperature_sensor.h

//This is the temperature sensor class derived from the analog_sensor BaseClass

#ifndef temperature_sensor_h
#define temperature_sensor_h

#include <Arduino.h>
#include "analog_sensor.h"

class TemperatureSensor : public AnalogSensor {

    private:

        int m_iB;
        float m_fResistance;

        void updateValue();

    public:
        TemperatureSensor(int analogPin);
        ~TemperatureSensor();

        float getData();
        
};

#endif
