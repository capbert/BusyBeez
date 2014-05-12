#include <MIDI.h>

#include "SimpleTimer.h"
#include "BBSensor.h"
#include "BBFlower.h"

#include "BBConstants.h"
#include "BBUtils.h"

#ifdef DEBUG

#include "MemoryFree.h"

#endif



// TODO: abstract MIDI calls aka ableton harnass?
// TODO: add thunder storm and flight of bumblebees


static SimpleTimer timer;
static int setTimerID;

void setup(){

  MIDI.begin(115200);
  Serial.begin(115200);

  
  LOGS("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
  LOGS("------ start ------");
  LOGS("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");





  LOG(freeMemory());  


  BBSensor::start(TRIGGER_PIN);

  configureRoom();
  configureFlowers();



  g_soundSetPool->setPool(g_soundSets, NUM_SOUNDS_SETS);
  // currentSoundSet = g_soundSetPool->getSet();

  getNewSoundSet();


  timer.setInterval(SENSOR_REFRESH_RATE, triggerSensorSync);
  
  // activateSoundSets();



}



void loop(){

  timer.run();

  updateSensors();

  delay(100);


}



void triggerSensorSync(){
  // LOGS("REFRESH");
  BBSensor::syncRead(TRIGGER_PIN, 1);
}

void updateSensors(){

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
    // g_FlowersVector[i]->enable();
    // g_FlowerSensors[i]->attach(&g_Room);
    // g_FlowerSensorVector[i]->attach(&g_Room);
  }

  // BBSensor::attachType(BBSensor::EZ, &g_Room);
}

void deactivateFlowers(){
  // LOGS("--- deactivate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i]->disable();
    // g_FlowersVector[i]->disable();
    // g_FlowerSensors[i]->detatch(&g_Room);
    // g_FlowerSensorVector[i]->detatch(&g_Room);
  }
  // BBSensor::detatchType(BBSensor::EZ, &g_Room);
}


void onRoomStateChangeCallback(BBRoom::RoomState state){
  if(state == BBRoom::ROOM_STATE_ACTIVE){
    activateFlowers();
    activateSoundSets();
  }else{
    deactivateFlowers();
    deactivateSoundSets();
  }
}



void configureRoom(){

  for(int i=0; i<NUM_ROOM_SENSORS; i++){
    // LOGS("config room");
      // BBSensor *sensor = BBSensor::create(roomConfig[i]);
      BBSensor *sensor = g_RoomSensors[i];
      sensor->attach(&g_Room);
      sensor->begin();

  }

  g_Room.setStateChangeCallback(onRoomStateChangeCallback);
  g_Room.setState(BBRoom::ROOM_STATE_INACTIVE);
}

void configureFlowers(){

  for (int i = 0; i < NUM_FLOWERS; ++i)
  {
    // BBFlower *flower = new BBFlower(fConfig[i].id, fConfig[i].numSamples);
    // BBSensor *sensor = BBSensor::create(sConfig[i]);
    BBSensor *sensor = g_FlowerSensors[i];
    // g_FlowerSensorVector.push_back(sensor);
    // g_FlowerSensors[i] = sensor;
    // g_Flowers[i] = flower;
    // g_FlowersVector.push_back(flower);
    // flower->disable();
    g_Flowers[i]->disable();
    sensor->attach(g_Flowers[i]);
    sensor->begin();
  }


}



void activateSoundSets(){

    // BBSensor::attachType(BBSensor::PIR, currentSoundSet);
  setTimerID = timer.setTimeout(getSoundSetTriggerTime(), triggerSoundSetClip);
  // for(int i=0; i<NUM_FLOWERS; i++){
  //   g_FlowerSensors[i]->attach(currentSoundSet);
  // }

}

void deactivateSoundSets(){
  // LOGS("detatch");
  //   // BBSensor::detatchType(BBSensor::PIR, currentSoundSet);
  // for(int i=0; i<NUM_FLOWERS; i++){
  //   g_FlowerSensors[i]->detatch(currentSoundSet);
  // }
  stopSoundSetClip();
  timer.deleteTimer(setTimerID);
}

void getNewSoundSet(){
  LOGS("----- GET NEW SOUND SET -----");
  // deactivateSoundSets();



  currentSoundSet = g_soundSetPool->getSet();

  currentSoundSet->print();
  // activateSoundSets();
}

// void startSoundSet(){
//   LOGS("startSoundSet");

//   // LOG(freeMemory());
//   activateSoundSets();
//   timer.setTimeout(1000, triggerSoundSetClip);
// }



void triggerSoundSetClip(){
  LOGS("triggerSoundSetClip");
  // deactivateSoundSets();
  currentSoundSet->stopClip(false);

  if (currentSoundSet->done()) getNewSoundSet();

  currentSoundSet->triggerClip(false);
  setTimerID = timer.setTimeout(getSoundSetTriggerTime(), stopSoundSetClip);
}

void stopSoundSetClip(){
  currentSoundSet->stopClip(true);
  setTimerID = timer.setTimeout(6500, triggerSoundSetClip);
}

// void startSoundSetClip(){}

int getSoundSetTriggerTime(){
  return getTriggerTime(MIN_SET_TRIGGER_TIME, MAX_SET_TRIGGER_TIME);
}

int getTriggerTime(int min, int max){
  return rand() % (max - min) + min;
}



// void printSensorValues(){
//   String vals;
  
//   // LOGS("print");

//   LOG(analogRead(A0));
//   // vals = String("Analog Values >>  A0: ") + analogRead(A0) + "   A1: " + analogRead(A1) + "   A2: " + analogRead(A2) + "   A3: " + analogRead(A3) + "   A4: " + analogRead(A4) + "   A5: " + analogRead(A5);
//   // vals = String("Digital Values >>  D2: ");
  
//     // String rawVals = String("A0: ") + analogRead(A0);

//   // for(int i=0; i<NUM_FLOWERS; i++){
//   //   int val = g_FlowerSensors[i]->read();
//   //   vals = vals + "   A" + i +": " + val ;
//   // }
//   // LOG("-----------");
//   // LOG(rawVals);
//   LOG(vals);


//   // delay(250);


// }

