#include <Arduino.h>
#include "BBRoom.h"
#include "BBSensor.h"
#include "BBUtils.h"
#include "BBSample.h"
BBRoom::BBRoom():Observer(){
  setState(ROOM_STATE_INACTIVE);
}
BBRoom::BBRoom(BBSample *samples, int numSamples):p_samples(samples), _numSamples(numSamples), Observer(){
  setState(ROOM_STATE_INACTIVE);

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

void BBRoom::update(Subject *subject){
  int sensorValue = ((BBSensor *)subject)->read();
  // printf("BBRoom sensor val: ");
  // print(sensorValue);



  if (_state == ROOM_STATE_ACTIVE){
    // sensor is off and room is active so turn it off
    if (sensorValue == -1){
      // Serial.println(F("room is active and sensor is off"));
      deactivateRoom();
    }
  }else if (_state == ROOM_STATE_INACTIVE){
    // sensor is on and room is inactive
    if(sensorValue == 1)
      activateRoom();
  }

}

void BBRoom::setStateChangeCallback(RoomUpdateCallback cb){
  _stateChangeCallback = cb;
}



// *********************************************************************************







void BBRoom::deactivateRoom(){
  // if (!noFlowerSamplesPlaying) return; // don't deactivate if flowers are playing
  printf("--- deactiveate room ---");
  // deactivateFlowers();
    setState(ROOM_STATE_INACTIVE);
    triggerRoomAmbienceOff();

  // }
}

void BBRoom::activateRoom(){
  
  printf("--- activate room ---");
  setState(ROOM_STATE_ACTIVE);
  triggerRoomAmbienceOn();
  // activateFlowers();

}

void BBRoom::triggerRoomAmbienceOn(){
  // trigger midi on
  printf("--- trigger room samples ON ---");
  for(int i = 0; i < _numSamples; i++){
    p_samples[i].triggerOn(true); 
  }
}

void BBRoom::triggerRoomAmbienceOff(){
  // trigger midi off
  // bool allOff = true;
  printf("--- trigger room samples OFF ---");
  for(int i = 0; i < _numSamples; i++){
    p_samples[i].triggerOff(true); 
    // allOff = g_Flowers[i].isTriggered() ? false : allOff;
  }
  // if(allOff){
  //   printf("trigger room off");    
  // }else{
  //   printf("room has not reached timeout yet... keep playing"); 
  // }
  
  // return allOff;
}