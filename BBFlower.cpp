#include <Arduino.h>

#include <stdlib.h>
#include "BBFlower.h"
#include "BBSensor.h"




BBFlower::BBFlower(){
  // empty
  // _enabled = true;
  // _numSamples = 7;
  enable();
}

BBFlower::BBFlower(BBSample *samples, int numSamples){
  // Serial.print(F("Initialize Flower")); 
  p_samples = samples;
  _numSamples = numSamples;
  enable();
}



void BBFlower::setSensor(BBSensor *sensor){
  p_sensor = sensor;
}

void BBFlower::update(){
  // Serial.print("update flower");
  // poll sensor
  // react 
  if(isDisabled()) return;


  int sensorValue = p_sensor->read();
  // Serial.println(F("sensor value: "));
  // Serial.println(sensorValue);


  (sensorValue == -1) ? stopSample() : triggerSample();
  




}


BBSample* BBFlower::getRandomSample(){
  // get item from array and return by reference
  int num = rand() % _numSamples;
  // Serial.print("getting random sample at index: ");
  // Serial.println(F("\n--getting random sample at index"));
  // Serial.println(rand());
  // Serial.println(num);
  BBSample* sample = p_samples + num;
  // BBSample sample = BBSample(1,2,3);
  // Serial.println(sample->description());
  return sample;
}

void BBFlower::disable(){
  _enabled = false;
  stopSample();
}

void BBFlower::enable(){
  _enabled = true;
}

bool BBFlower::isDisabled(){
  return !_enabled;
}

bool BBFlower::isTriggered(){
  return !!_sampleTriggered;
}


// void BBFlower::setSamples(BBSample *samples, int numSamples){
//   _numSamples = numSamples;
//   p_samples = samples;
// }





/* PRIVATE */

void BBFlower::triggerSample(){
  if (_sampleTriggered) return;
  // Serial.println(*p_sensor, HEX)
  // Serial.println(F("trigger sample"));
  _sampleTriggered = true;

  p_currentSample = getRandomSample(); 
  p_currentSample->triggerOn();
  // Serial.println(p_currentSample->description());

}

void BBFlower::stopSample(){
  if(!_sampleTriggered) return;
  // Serial.println(F("stopping sample"));
  if(p_currentSample->canRetrigger()){
    p_currentSample->triggerOff();
    _sampleTriggered = false;
  }
}







