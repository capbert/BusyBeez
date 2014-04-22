#include <MIDI.h>

// #include "SimpleTimer.h"

#include "BBSample.h"
#include "BBSensor.h"
#include "BBFlower.h"

#include "BBConstants.h"
#include "BBUtils.h"
#include "StandardCplusplus.h"


#include <vector>
// #include "StandardCplusplus.h"
// #include "system_configuration.h"
// #include "unwind-cxx.h"
// #include "utility.h"


int roomSensePin = 2;                                                   //motion sensor digital pin def
int proxSensePin1 = 1;                                                  //proximity sensor analog pin def
// static const int NUM_FLOWER_SAMPLES = 7;
// static const int NUM_FLOWERS = 2;
// static const int NUM_AMBIENCE_SAMPLES = 2;

// bool noFlowerSamplesPlaying = true;


// enum RoomState {
//   ROOM_STATE_ACTIVE,
//   ROOM_STATE_INACTIVE
// };

// RoomState roomState;




void setup(){

  MIDI.begin(115200);
  Serial.begin(115200);

  configureRoom();
  configureFlowers();
  
  deactivateFlowers();

}



void loop(){
  

  g_RoomMotionSensor.update();


  // if(g_Room.getState() == BBRoom::ROOM_STATE_ACTIVE){
  for(int i=0; i<NUM_FLOWERS; i++){
    g_FlowerSensors[i].update();
  }

  // }

  
  
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

    if (i==4) sensor->setInputRange(20,144); // FIXME: config the lone ultrasonic sensor

    sensor->attach(&g_Flowers[i]);
    sensor->begin();
  }
}
