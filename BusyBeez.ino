#include <MIDI.h>


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

static const int SENSOR_REFRESH = 60 * NUM_FLOWERS;


void setup(){

  MIDI.begin(115200);
  Serial.begin(115200);

  
  LOGS("------ start ------");

  LOG(freeMemory());


  // BBSensor::beginConstantLoop(RX_PIN, TX_PIN, 50);
  BBSensor::start(TRIGGER_PIN);

  configureRoom();
  
  configureFlowers();


}

void loop(){

  if(millis() % SENSOR_REFRESH < 110){
    LOGS("- refresh -");
    BBSensor::syncRead(TRIGGER_PIN, 1);
  }

  // if(millis() % 10000 < 110){
  //   LOGS("- still running - ");
  //   LOG(freeMemory());
  // }

  BBSensor::updateAll();

  printSensorValues();
  // g_soundSetPool->updateAll();
  
  delay(100);
  // delay(SENSOR_REFRESH);
}


// void updateSensors(){

//   for(int i=0; i<NUM_ROOM_SENSORS; i++){
//     g_RoomSensors[i]->update();
//   }

//   for(int i=0; i<NUM_FLOWERS; i++){
//     g_FlowerSensors[i]->update();
//   }

// }


void activateFlowers(){
  // LOGS("--- activate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i]->enable();
    // g_FlowersVector[i]->enable();
    g_FlowerSensors[i]->attach(&g_Room);
    // g_FlowerSensorVector[i]->attach(&g_Room);
  }
}

void deactivateFlowers(){
  // LOGS("--- deactivate flowers ---");
  for(int i = 0; i< NUM_FLOWERS; i++){
    g_Flowers[i]->disable();
    // g_FlowersVector[i]->disable();
    g_FlowerSensors[i]->detatch(&g_Room);
    // g_FlowerSensorVector[i]->detatch(&g_Room);
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
      BBSensor *sensor = BBSensor::create(roomConfig[i]);
      // BBSensor *sensor = g_RoomSensors[i];
      sensor->attach(&g_Room);
      sensor->begin();

  }

  g_Room.setStateChangeCallback(onRoomStateChangeCallback);
  g_Room.setState(BBRoom::ROOM_STATE_INACTIVE);
}

void configureFlowers(){
  // TODO: need to figure out a way to configure these in a more meaningful way.
  // for(int i=0; i<NUM_FLOWERS; i++){
  //   LOGS("config flowers");
  //   BBSensor *sensor = g_FlowerSensors[i];
  //   sensor->attach(g_Flowers[i]);
  //   sensor->begin();
  // }


  for (int i = 0; i < NUM_FLOWERS; ++i)
  {
    BBFlower *flower = new BBFlower(fConfig[i].id, fConfig[i].numSamples);
    BBSensor *sensor = BBSensor::create(fConfig[i].sensor);
    // g_FlowerSensorVector.push_back(sensor);
    g_FlowerSensors[i] = sensor;
    g_Flowers[i] = flower;
    // g_FlowersVector.push_back(flower);
    flower->disable();

    sensor->attach(flower);
    sensor->begin();
  }


}








void printSensorValues(){
  String vals;

  // vals = String("Analog Values >>  A0: ") + analogRead(A0) + "   A1: " + analogRead(A1) + "   A2: " + analogRead(A2) + "   A3: " + analogRead(A3) + "   A4: " + analogRead(A4) + "   A5: " + analogRead(A5);
  // vals = String("Digital Values >>  D2: ") + digitalRead(2) + "   D3: " + digitalRead(3) + "   D4: " + digitalRead(4); 
  
    // String rawVals = String("A0: ") + analogRead(A0);

  for(int i=0; i<NUM_FLOWERS; i++){
    int val = g_FlowerSensors[i]->read();
    vals = vals + "   A" + i +": " + val ;
  }
  // LOG("-----------");
  // LOG(rawVals);
  LOG(vals);


  // delay(250);


}

