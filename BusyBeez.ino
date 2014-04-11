#include <MIDI.h>
// #include <midi_Defs.h>
// #include <midi_Namespace.h>
// #include <midi_Settings.h>

#include "SimpleTimer.h"

#include "BBSample.h"
#include "BBSensor.h"
#include "BBFlower.h"

#include "BBConstants.h"
#include "BBUtils.h"

// #include "SimpleTimer.h"





int roomSensePin = 2;                                                   //motion sensor digital pin def
int proxSensePin1 = 1;                                                  //proximity sensor analog pin def
// static const int NUM_FLOWER_SAMPLES = 7;
// static const int NUM_FLOWERS = 2;
// static const int NUM_AMBIENCE_SAMPLES = 2;

bool noFlowerSamplesPlaying = true;


enum RoomState {
  ROOM_STATE_ACTIVE,
  ROOM_STATE_CLOSING,
  ROOM_STATE_INACTIVE
};

RoomState roomState = ROOM_STATE_INACTIVE;



void setup(){
  // timer.setInterval(500, testFn);


  // for(int i = 0; i<NUM_FLOWER_SAMPLES; i++){
  //   g_FlowerSamples[i].setTimer(&g_Timer);
  // }
  // for(int j = 0; j<NUM_AMBIENCE_SAMPLES; j++){
  //   g_AmbienceSamples[j].setTimer(&g_Timer);
  // }




  MIDI.begin(115200);
  Serial.begin(115200);

  // attachInterrupt(0, activateRoom, RISING); // activate the room on motion

  // setTime(0,0,0,1,1,00);
  
  g_RoomMotionSensor.setPin(2);
  g_RoomMotionSensor.setInputRange(0,1);
  g_RoomMotionSensor.setOutputRange(0,1);



  g_FlowerProximitySensor0.setPin(0);
  g_FlowerProximitySensor1.setPin(1);
  // proxSensor2.setPin(2);
  // proxSensor3.setPin(3);
  // proxSensor4.setPin(4);
  // proxSensor5.setPin(5);



  g_Flowers[0].setSensor(&g_FlowerProximitySensor0);
  g_Flowers[1].setSensor(&g_FlowerProximitySensor1);
  // g_Flowers[2].setSensor(&proxSensor2);
  // g_Flowers[3].setSensor(&proxSensor3);
  // g_Flowers[4].setSensor(&proxSensor4);

  // g_Flowers[5].setSensor(&proxSensor5);
}

void loop(){

  // g_Timer.run();
  // g_flowerSamples->triggerOff();

  checkRoomState();

  if(roomState == ROOM_STATE_ACTIVE){
    updateFlowers();
  }

  // printf("testing the printer");

  delay(100);
}


void updateFlowers(){
  bool allOff = true;
  for( int i = 0; i<NUM_FLOWERS; i++){
    // Serial.print("Updating flower at index: ");
    // Serial.println(i);

    g_Flowers[i].update();
    allOff = g_Flowers[i].isTriggered() ? false : allOff;
  }
  // if all flowers are 'off' then the room can close
  
  if(allOff){
    printf("update flowers: all off");
  }else{
    printf("update flowers: still running");
  }
  // print(allOff);
  noFlowerSamplesPlaying = allOff;
}

void checkRoomState(){
  // poll room sensors... only one right now
  int sensorVal = g_RoomMotionSensor.read();


  if (roomState == ROOM_STATE_ACTIVE){
    // sensor is off and room is active so turn it off
    if (sensorVal == -1){
      // Serial.println(F("room is active and sensor is off"));
      deactivateRoom();
    }
  }else if (roomState == ROOM_STATE_INACTIVE){
    // sensor is on and room is inactive
    if(sensorVal == 1)
      activateRoom();
  }

}



void activateFlowers(){
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i].enable();
  }
}

void deactivateFlowers(){
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i].disable();
  }
}

void deactivateRoom(){
  // Serial.println(F("--- deactivate room\n ---"));
  if (noFlowerSamplesPlaying) return; // don't deactivate if flowers are playing
  deactivateFlowers();
  if (triggerRoomAmbienceOff()){
    setRoomState(ROOM_STATE_INACTIVE);
  }
}

void activateRoom(){
  printf("--- activate room ---");
  setRoomState(ROOM_STATE_ACTIVE);
  activateFlowers();
  triggerRoomAmbienceOn();

}

void setRoomState(RoomState state){
  // Not sure if more needs to happen to set room state --- so I abstracted it.
  if(state == ROOM_STATE_ACTIVE){
    printf("setting ROOM_STATE_ACTIVE");
  }else{
    printf("setting ROOM_STATE_INACTIVE");

  }
  roomState = state;
}

void triggerRoomAmbienceOn(){
  // trigger midi on
  printf("trigger room on");
  for(int i = 0; i < NUM_AMBIENCE_SAMPLES; i++){
    g_AmbienceSamples[i].triggerOn(); 
  }
}

bool triggerRoomAmbienceOff(){
  // trigger midi off
  bool allOff = true;
  for(int i = 0; i < NUM_AMBIENCE_SAMPLES; i++){
    g_AmbienceSamples[i].triggerOff(); 
    allOff = g_Flowers[i].isTriggered() ? false : allOff;
  }
  if(allOff){
    printf("trigger room off");    
  }else{
    printf("room has not reached timeout yet... keep playing");
  }
  
  return allOff;
}



