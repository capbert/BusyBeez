#include <Arduino.h>
#include "PIRSensor.h"
#include "BBSensor.h"
#include "BBUtils.h"
PIRSensor::PIRSensor(int pin):
BBSensor(pin, PIR)
{

  setInputRange(0,1);
  setOutputRange(0,1);
}

int PIRSensor::readSensor(){
  // LOGS("PIR: readSensor");

  // LOG(_sensorType);
  return digitalRead(getPin());
}

void PIRSensor::begin(){
  // LOG("PIR: begin"); 
  pinMode(getPin(), INPUT);
  BBSensor::begin();
}