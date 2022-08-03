#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\light_sensor.h"
// light_sensor

//This is the light sensor class derived from the analog_sensor BaseClass

#ifndef light_sensor
#define light_sensor

#include <Arduino.h>
#include "analog_sensor.h"

class LightSensor : public AnalogSensor {

    private:

        void updateValue();
    public:
        LightSensor(int analogPin);
        ~LightSensor();

        float getData();
        
};

#endif
