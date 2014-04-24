#include <MIDI.h>

// #include "SimpleTimer.h"

#include "BBSample.h"
#include "BBSensor.h"
#include "BBFlower.h"

#include "BBConstants.h"
#include "BBUtils.h"

// #include "MemoryFree.h"


void setup(){

  MIDI.begin(115200);
  Serial.begin(115200);

  
  // printf("start");
  // print(freeMemory());

  configureRoom();
  configureFlowers();
  
  deactivateFlowers();
}



void loop(){
  
  // printf("loop - "); 
  // print(freeMemory());
  
  g_RoomMotionSensor.update();

  for(int i=0; i<NUM_FLOWERS; i++){
    g_FlowerSensors[i].update();
  }
  
  delay(1);
}









void activateFlowers(){
  // printf("--- activate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i].enable();
  }
}

void deactivateFlowers(){
  // printf("--- deactivate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i].disable();
    // g_Flowers[i].stopSample();
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

  g_RoomMotionSensor.setInputRange(0,1);
  g_RoomMotionSensor.setOutputRange(0,1);

  g_RoomMotionSensor.attach(&g_Room);
  g_RoomMotionSensor.begin();

  g_Room.setStateChangeCallback(onRoomStateChangeCallback);
  g_Room.setState(BBRoom::ROOM_STATE_INACTIVE);
}

void configureFlowers(){
  // TODO: need to figure out a way to configure these in a more meaningful way.

  for(int i=0; i<NUM_FLOWERS; i++){
    BBSensor *sensor = &g_FlowerSensors[i];
    if (i==4) sensor->setInputRange(20,144); // TODO: FIXME: config the lone ultrasonic 

    sensor->attach(&g_Flowers[i]);
    sensor->begin();
  }
}
