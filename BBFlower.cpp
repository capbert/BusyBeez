#include <Arduino.h>
#include <stdlib.h>

#include <MIDI.h>

#include "BBFlower.h"
#include "BBSensor.h"

#include "BBUtils.h"


BBFlower::BBFlower(int id, int numSamples):
  _id(id),
  _numSamples(numSamples)
{
  setTimeout(DEFAULT_TIMEOUT); // TODO: remove!!!
  setState(FLOWER_STATE_INACTIVE);
}


// GETTER SETTER ------------------- 

void BBFlower::setID(int id){
  _id = id;
}

int BBFlower::getID(){
  return _id;
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



// BBSample* BBFlower::getRandomSample(){
//   // get item from array and return by reference
//   int num = rand() % _numSamples;
//   BBSample* sample = p_samples + num;
//   return sample;
// }

void BBFlower::triggerSample(){
  if (getState() == FLOWER_STATE_ACTIVE) return; // don't trigger if already triggered

  LOGS("BBFlower::trigger sample");
  _currentNote = rand() % _numSamples;
  MIDI.sendNoteOn(_currentNote, 127, _id+1); // TODO: channels start at 1
  MIDI.sendNoteOn(123, 127, _id+1); // set unity gain
  // p_currentSample = getRandomSample(); 
  // p_currentSample->assignToOutput(_speakerOutputID);
  // p_currentSample->triggerOn();

}

void BBFlower::stopSample(bool fade){
  if(getState() == FLOWER_STATE_INACTIVE) return; // don't do anything if nothing is triggered

  LOGS("BBFlower::stop sample");

  if(fade){
    LOGS("  with fade");
    MIDI.sendNoteOn(125, 127, _id+1);
  }else{
    LOGS("  without fade");
    MIDI.sendNoteOn(_currentNote, 0, _id+1);
  }
  // p_currentSample->triggerOff();

}

void BBFlower::update(ISubject *subject){
    // LOGS("--------updateing BBFlower--------");

    int sensorValue = ((BBSensor*)subject)->read();
    FlowerState state = getState();

    if ( state == FLOWER_STATE_ACTIVE || state == FLOWER_STATE_FADEOUT ){
      // LOG("active");
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

   /* 
   DEGUG


   if (getState()== FLOWER_STATE_INACTIVE){
      setState(FLOWER_STATE_ACTIVE);
    }

    updateTimeout();

    */

}

void BBFlower::handleTimeout(){
  if(getState() == FLOWER_STATE_ACTIVE){
    LOGS("handle INITIAL timeout");
    setTimeout(FADE_OUT_TIME);
    stopSample(true);  
    setState(FLOWER_STATE_FADEOUT);
    
    
  }else{
    LOGS("handle FADE timeout");
    stopSample();
    setState(FLOWER_STATE_INACTIVE);
    setTimeout(DEFAULT_TIMEOUT);
  }
}


void BBFlower::setState(BBFlower::FlowerState state){
  if (state == _state) return;
  // LOGS("----- SET FLOWER STATE -----");
  // LOG(state);
  _state = state;
}

BBFlower::FlowerState BBFlower::getState(){
  return _state;
}




