#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\analog_sensor.h"
// analog_sensor.h

//This is the BaseClass to read analog devices

#ifndef analog_sensor_h
#define analog_sensor_h

#include <Arduino.h>

class AnalogSensor {

  private:
      char *m_cDeviceName;
      int m_iPin;
      float m_fRawValue;
      float m_fValue;

  protected:

      void updateRawValue();


      char *getDeviceName();
      int getPin();

      void virtual updateValue() = 0;
      void setDeviceName(char *deviceName);
      void setPin(int pin);
      void setRawData(float value);
      void setData(float value);

      void print(float value);

    public:

      AnalogSensor(char *deviceName, int analogPin);
      ~AnalogSensor();

      float getData();
      float getRawData();

      void printData();  
      void printRawData();  
};

#endif
