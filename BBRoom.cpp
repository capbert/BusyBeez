#include <Arduino.h>
#include <MIDI.h>
#include "BBRoom.h"
#include "BBSensor.h"
#include "BBUtils.h"
#include "BBSample.h"


BBRoom::BBRoom(BBSample *samples, int numSamples):
  p_samples(samples), 
  _numSamples(numSamples)
{
  setTimeout(DEFAULT_TIMEOUT); //TODO: REMOVE
  setState(ROOM_STATE_INACTIVE);
  // _activatedTime = 0;
}

BBRoom::RoomState BBRoom::getState(){
  return _state;
}


void BBRoom::setState(BBRoom::RoomState state){
  _state = state;
  if(_stateChangeCallback){
    _stateChangeCallback(_state);
  }
}

void BBRoom::update(ISubject *subject){
  int sensorValue = ((BBSensor *)subject)->read();

  if (_state == ROOM_STATE_ACTIVE){
    // sensor is off and room is active so turn it off
    if (sensorValue < 0){

    // only allow room to deactivate after min time... 
      updateTimeout();
    }

  }else if (_state == ROOM_STATE_INACTIVE){
    // sensor is on and room is inactive

    if(sensorValue == 1)
      activateRoom();
  }

}


void BBRoom::handleTimeout(){
  deactivateRoom();
}


void BBRoom::setStateChangeCallback(RoomUpdateCallback cb){
  _stateChangeCallback = cb;
}



// *********************************************************************************


void BBRoom::deactivateRoom(){
  printf("--- deactiveate room ---");
    resetTimeout();
    setState(ROOM_STATE_INACTIVE);
    triggerRoomAmbienceOff();
}

void BBRoom::activateRoom(){
  
  printf("--- activate room ---");
  setState(ROOM_STATE_ACTIVE);
  triggerRoomAmbienceOn();

}


void BBRoom::triggerRoomAmbienceOn(){
  // trigger midi on
  printf("--- trigger room samples ON ---");
  for(int i = 0; i < _numSamples; i++){
    p_samples[i].triggerOn(false); 
  }
  MIDI.sendNoteOn(59, 127, 1); // TODO: trigger 'global' fadeOut
}

void BBRoom::triggerRoomAmbienceOff(){

  printf("--- trigger room samples OFF ---");
  // for(int i = 0; i < _numSamples; i++){
  //   p_samples[i].triggerOff(true); 
  // }

  MIDI.sendNoteOn(58, 127, 1); // TODO: trigger 'global' fadeOut

}