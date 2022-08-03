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

      void print(float value);

  protected:

      void updateRawValue();
      void virtual updateValue() = 0;
      char *getDeviceName();
      int getPin();

      void setDeviceName(char *deviceName);
      void setPin(int pin);
      void setRawData(float value);
      void setData(float value);

    public:

      AnalogSensor(char *deviceName, int analogPin);
      virtual  ~AnalogSensor() {};

      float getRawValue();
      float getValue();
      float getData();

      void printData();
      void printRawData();

};

#endif
