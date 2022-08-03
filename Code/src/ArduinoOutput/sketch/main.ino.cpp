#include <Arduino.h>
#line 1 "c:\\Users\\javig\\Desktop\\Proyecto\\Spresense\\Code\\src\\main\\main.ino"
// main code: main.code

#include <iostream>
#include "temperature_sensor.h"
#include "moisture_sensor.h"
#include "light_sensor.h"
#include "analog_sensor.h"

#include <Spresense_inferencing.h>
#include <audioPlayer/audio_player.h>


LightSensor LightDevice(A0);
MoistureSensor MoistureDevice(A1);
TemperatureSensor TempDevice(A2);

AudioPlayer AudioDevice;

void setup() {

  Serial.begin(9600);

  AudioDevice.init();

  Serial.println("Edge Impulse Inferencing Demo");

  // summary of inferencing settings (from model_metadata.h)
  ei_printf("Inferencing settings:\n");
  ei_printf("\tInterval: %.2f ms.\n", (float)EI_CLASSIFIER_INTERVAL_MS);
  ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
  ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
  ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) /
                                          sizeof(ei_classifier_inferencing_categories[0]));
}

void loop() {



  /*TempDevice.printData();
  LightDevice.printData();
  MoistureDevice.printData();
  delay(1000);*/
  
}

