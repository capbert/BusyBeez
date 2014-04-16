#include <Arduino.h>

#include <stdlib.h>
#include "BBFlower.h"
#include "BBSensor.h"

#include "BBUtils.h"


BBFlower::BBFlower():Observer(){
  enable();
}

BBFlower::BBFlower(BBSample *samples, int numSamples):Observer(){
  p_samples = samples;
  _numSamples = numSamples;
  enable();
}

void BBFlower::setSensor(BBSensor *sensor){
  p_sensor = sensor;
}

BBSample* BBFlower::getRandomSample(){
  // get item from array and return by reference
  int num = rand() % _numSamples;

  // printf("BBFlower::getRandomSample");
  // print(num);
  // printf("------------------");


  BBSample* sample = p_samples + num;
  return sample;
}

void BBFlower::disable(){
  _enabled = false;
  // stopSample();
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

void BBFlower::triggerSample(){
  if (_sampleTriggered) return; // don't trigger if already triggered

  // printf("BBFlower::trigger sample");
  _sampleTriggered = true;
  _activatedTime = millis();
  p_currentSample = getRandomSample(); 
  p_currentSample->triggerOn();

}

void BBFlower::stopSample(){
  if(!_sampleTriggered) return; // don't do anything if nothing is triggered

  if(getElapsedTime() > MIN_PLAYBACK_DURATION){
    // printf("BBFlower::stop sample");
    p_currentSample->triggerOff();
    // p_currentSample = NULL;
    _sampleTriggered = false;
  }
}

void BBFlower::update(Subject *subject){
    // printf("--------updateing BBFlower--------");

    // TODO: does this really make sense? it seems hacky
    if(isDisabled() && _sampleTriggered) stopSample();
    if(isDisabled()) return;

    int sensorValue = ((BBSensor*)subject)->read();

    (sensorValue == -1) ? stopSample() : triggerSample();

}


long BBFlower::getElapsedTime(){
  return millis() - _activatedTime;
}







