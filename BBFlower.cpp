#include <Arduino.h>

#include <stdlib.h>

#include "BBFlower.h"
#include "BBSensor.h"

#include "BBUtils.h"


// BBFlower::BBFlower(){
//   enable();
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
  resetTimeout();
  if(getState()== FLOWER_STATE_ACTIVE) // TODO: is this wrong? is something actually playing?s
    stopSample();  
  setState(FLOWER_STATE_DISABLED);
  // _enabled = false;
}

void BBFlower::enable(){
  // _enabled = true;
  setState(FLOWER_STATE_INACTIVE);
}

void BBFlower::triggerSample(){
  if (getState() == FLOWER_STATE_ACTIVE) return; // don't trigger if already triggered

  printf("BBFlower::trigger sample");
  // _sampleTriggered = true;

  p_currentSample = getRandomSample(); 
  p_currentSample->assignToOutput(_speakerOutputID);
  p_currentSample->triggerOn();

}

void BBFlower::stopSample(){
  if(getState() == FLOWER_STATE_INACTIVE) return; // don't do anything if nothing is triggered

  // if(getElapsedTime() > MAX_INACTIVITY_DURATION){
    printf("BBFlower::stop sample");
    p_currentSample->triggerOff();
    // p_currentSample = NULL;
    // _sampleTriggered = false;
  // }
}

void BBFlower::update(ISubject *subject){
    // printf("--------updateing BBFlower--------");

    int sensorValue = ((BBSensor*)subject)->read();
    
    FlowerState state = getState();

    if ( state == FLOWER_STATE_ACTIVE ){

      if (sensorValue < 0){
      
        updateTimeout();
          
     }else{
      // TODO: do something with the sensor value??
     }

    }else if (state == FLOWER_STATE_INACTIVE){

      if(sensorValue >= 0){
        triggerSample();
        setState(FLOWER_STATE_ACTIVE);
      }

    }



    // (sensorValue == -1) ? stopSample() : triggerSample();

}

void BBFlower::handleTimeout(){
  resetTimeout();
  stopSample();  
  setState(FLOWER_STATE_INACTIVE);
}

// void BBFlower::updateTimeout(){

//   if(timeoutHasExpired()){
//     printf("---- timeout has expired ----");
//     handleTimeout();

//   } else {

//     startTimeout();

//   }

// }

// void BBFlower::setTimeout(int timeout){
//   _timeout = timeout;
// }

// bool BBFlower::timeoutHasExpired(){
//   // printf("TIME: ");
//   // print(_timeoutStart);
//   return ( getElapsedTime() > _timeout ) ? true : false;
// }

// void BBFlower::startTimeout(){

//   if(_timeoutStart == 0){
//     _timeoutStart = millis();
//   }

// }

// void BBFlower::resetTimeout(){
//   // 0 = "off" in this case. This may be a poor asumption.
//   _timeoutStart = 0;
// }

// long BBFlower::getElapsedTime(){
//   if (_timeoutStart > 0){
//     return millis() - _timeoutStart;
//   }else{
//     return 0;
//   }
// }


void BBFlower::setState(BBFlower::FlowerState state){
  if (state == _state) return;
  printf("----- SET FLOWER STATE -----");
  print(state);
  _state = state;
}

BBFlower::FlowerState BBFlower::getState(){
  return _state;
}




