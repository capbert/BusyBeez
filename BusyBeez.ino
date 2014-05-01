#include <MIDI.h>

// #include "SimpleTimer.h"

// #include "BBSample.h"
#include "BBSensor.h"
#include "BBFlower.h"

#include "BBConstants.h"
#include "BBUtils.h"

#ifdef DEBUG

#include "MemoryFree.h"

#endif



// TODO: abstract MIDI calls aka ableton harnass?
// TODO: configure sensors and flowers using config struct objs


void setup(){

  MIDI.begin(115200);
  Serial.begin(115200);

  
  LOGS("------ start ------");

  LOG(freeMemory());


  configureRoom();
  configureFlowers();

  deactivateFlowers();
  // activateFlowers();
}



void loop(){
  
  BBSensor::syncronize(RX_PIN, 50,50);

  for(int i=0; i<NUM_ROOM_SENSORS; i++){
    g_RoomSensors[i]->update();
  }

  for(int i=0; i<NUM_FLOWERS; i++){
    g_FlowerSensors[i]->update();
  }

}




void activateFlowers(){
  // LOGS("--- activate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i]->enable();
    g_FlowerSensors[i]->attach(&g_Room);
  }
}

void deactivateFlowers(){
  // LOGS("--- deactivate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i]->disable();
    g_FlowerSensors[i]->detatch(&g_Room);
  }
}


void onRoomStateChangeCallback(BBRoom::RoomState state){
  if(state == BBRoom::ROOM_STATE_ACTIVE){
    activateFlowers();
  }else{
    deactivateFlowers();
  }
}

void configureRoom(){

  for(int i=0; i<NUM_ROOM_SENSORS; i++){
    LOGS("config room");
      BBSensor *sensor = g_RoomSensors[i];
      sensor->attach(&g_Room);
      sensor->begin();
  }

  g_Room.setStateChangeCallback(onRoomStateChangeCallback);
  g_Room.setState(BBRoom::ROOM_STATE_INACTIVE);
}

void configureFlowers(){
  // TODO: need to figure out a way to configure these in a more meaningful way.
  for(int i=0; i<NUM_FLOWERS; i++){
    LOGS("config flowers");
    EZSensor *sensor = g_FlowerSensors[i];
    // sensor->setInputRange(20,144); // TODO: FIXME: config the lone ultrasonic 
    sensor->attach(g_Flowers[i]);
    sensor->begin();
  }
}
