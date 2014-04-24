#include <Arduino.h>

#include <stdlib.h>

#include "BBFlower.h"
#include "BBSensor.h"

#include "BBUtils.h"


// BBFlower::BBFlower(){
//   // enable();
// }

BBFlower::BBFlower(BBSample *samples, int numSamples, int speakerID):
  p_samples(samples),
  _numSamples(numSamples),
  _speakerOutputID(speakerID)
  {

  setTimeout(DEFAULT_TIMEOUT); // TODO: remove!!!
  setState(FLOWER_STATE_INACTIVE);

}




void BBFlower::setSensor(BBSensor *sensor){
  p_sensor = sensor;
}

BBSample* BBFlower::getRandomSample(){
  // get item from array and return by reference
  int num = rand() % _numSamples;
  BBSample* sample = p_samples + num;
  return sample;
}

void BBFlower::disable(){
  // resetTimeout();
  if(getState()== FLOWER_STATE_ACTIVE) stopSample(); // TODO: is this wrong? is something actually playing?s
    
  setState(FLOWER_STATE_DISABLED);
}

void BBFlower::enable(){
  // _enabled = true;
  setState(FLOWER_STATE_INACTIVE);
}

void BBFlower::triggerSample(){
  if (getState() == FLOWER_STATE_ACTIVE) return; // don't trigger if already triggered

  printf("BBFlower::trigger sample");

  p_currentSample = getRandomSample(); 
  p_currentSample->assignToOutput(_speakerOutputID);
  p_currentSample->triggerOn();

}

void BBFlower::stopSample(){
  if(getState() == FLOWER_STATE_INACTIVE) return; // don't do anything if nothing is triggered

  printf("BBFlower::stop sample");
  p_currentSample->triggerOff();

}

void BBFlower::update(ISubject *subject){
    // printf("--------updateing BBFlower--------");

    int sensorValue = ((BBSensor*)subject)->read();
    // print(sensorValue);
    FlowerState state = getState();

    if ( state == FLOWER_STATE_ACTIVE ){

      if (sensorValue < 0){
      
        // updateTimeout();
          
     }else{
      // TODO: do something with the sensor value??
     }

    }else if (state == FLOWER_STATE_INACTIVE){

      if(sensorValue >= 0){
        triggerSample();
        setState(FLOWER_STATE_ACTIVE);
      }

    }


}

void BBFlower::handleTimeout(){
  resetTimeout();
  stopSample();  
  setState(FLOWER_STATE_INACTIVE);
}


void BBFlower::setState(BBFlower::FlowerState state){
  if (state == _state) return;
  // printf("----- SET FLOWER STATE -----");
  print(state);
  _state = state;
}

BBFlower::FlowerState BBFlower::getState(){
  return _state;
}




