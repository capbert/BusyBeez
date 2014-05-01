#include <Arduino.h>
#include <MIDI.h>
#include "BBRoom.h"
#include "BBSensor.h"
#include "BBUtils.h"
// #include "BBSample.h"


BBRoom::BBRoom(int numSamples):
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
    }else{
      resetTimeout();
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
  LOGS("--- deactiveate room ---");
    resetTimeout();
    setState(ROOM_STATE_INACTIVE);
    triggerRoomAmbienceOff();
}

void BBRoom::activateRoom(){
  
  LOGS("--- activate room ---");
  setState(ROOM_STATE_ACTIVE);
  triggerRoomAmbienceOn();

}


void BBRoom::triggerRoomAmbienceOn(){
  // trigger midi on
  LOGS("--- trigger room samples ON ---");
  for(int i = 0; i < _numSamples; i++){
    // p_samples[i].triggerOn(false); 
    MIDI.sendNoteOn(i,127,16);
  }
  // TODO: what is the deal with triggering ambience samples?
  MIDI.sendNoteOn(126, 127, 16); // TODO: trigger 'global' fadeOut
}

void BBRoom::triggerRoomAmbienceOff(){

  LOGS("--- trigger room samples OFF ---");
  // for(int i = 0; i < _numSamples; i++){
  //   p_samples[i].triggerOff(true); 
  //   MIDI.sendNoteOn(i,127,16);
  // }
  // TODO: set timer for fade time
  
  MIDI.sendNoteOn(127, 127, 16); // TODO: trigger 'global' fadeOut

}