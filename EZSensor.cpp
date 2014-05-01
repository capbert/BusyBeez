#include <Arduino.h>

#include "EZSensor.h"
#include "BBSensor.h"
#include "BBUtils.h"
EZSensor::EZSensor(int pin):
BBSensor(pin, EZ)
{
  setInputRange(24,144); // roughly 1-6ft
  setOutputRange(0,127);
  invertOutput(true);
}

int EZSensor::readSensor(){
  // LOGS("read EZSensor");
  
  return analogRead(getPin());
}

void EZSensor::begin(){
  // LOGS("BEGIN EZ");
  BBSensor::begin();
}