
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"
#include "BBSensor.h"
#include "EZSensor.h"
#include "PIRSensor.h"
#include "BBSoundSetPool.h"
#include "BBSoundSet.h"


static const int TRIGGER_PIN = 13;

// =========================== Sensors ===========================

static const int NUM_ROOM_SENSORS = 3;

static const SensorDescription roomConfig[NUM_ROOM_SENSORS] = {
  { BBSensor::PIR, 2, {0,1}, {0,1} },
  { BBSensor::PIR, 3, {0,1}, {0,1} },
  { BBSensor::PIR, 4, {0,1}, {0,1} }
};





// =========================== Room ===========================

static const int NUM_AMBIENCE_SAMPLES = 1;
static BBRoom g_Room(NUM_AMBIENCE_SAMPLES);



// =========================== Flowers ===========================




static const int NUM_FLOWERS = 6;


static const SensorDescription sConfig[NUM_FLOWERS] ={
  {BBSensor::EZ, A0, {12,40}, {0,127}},
  {BBSensor::EZ, A1, {12,60}, {0,127}},
  {BBSensor::EZ, A2, {12,40}, {0,127}},
  {BBSensor::EZ, A3, {12,60}, {0,127}},
  {BBSensor::EZ, A4, {12,60}, {0,127}},
  {BBSensor::EZ, A5, {12,25}, {0,127}}
};


// static const FlowerDescription fConfig[NUM_FLOWERS] = {
//   {0, 2, {BBSensor::EZ, A0, {12,40}, {0,127}}},
//   {1, 2, {BBSensor::EZ, A1, {12,60}, {0,127}}},
//   {2, 2, {BBSensor::EZ, A2, {12,40}, {0,127}}},
//   {3, 2, {BBSensor::EZ, A3, {12,60}, {0,127}}},
//   {4, 2, {BBSensor::EZ, A4, {12,60}, {0,127}}},
//   {5, 2, {BBSensor::EZ, A5, {12,25}, {0,127}}},
// };


static BBFlower *g_Flowers[NUM_FLOWERS] = {

  new BBFlower(0, 7),
  new BBFlower(1, 7),
  new BBFlower(2, 7),
  new BBFlower(3, 7),
  new BBFlower(4, 7),
  new BBFlower(5, 7)

};


// =========================== Sound Sets ===========================

static BBSoundSetPool *g_soundSetPool = BBSoundSetPool::getInstance();
static BBSoundSet* currentSoundSet;
// static SoundSetDescription setConfig[NUM_SOUNDS_SETS] = {
//   {7, 0, 9, true},
//   {7, 9, 6, true},
//   {7, 15, 6, true},
//   {8, 0, 5, true},
//   {8, 5, 5, true},
//   {8, 10, 5, true},
//   {8, 15, 4, true},
//   {8, 19, 4, true},
//   {8, 23, 4, true},
//   {8, 27, 4, true},
//   {8, 31, 5, true},
//   {10, 0, 4, true},
// };


static const int NUM_SOUNDS_SETS = 12;
static BBSoundSet *g_soundSets[NUM_SOUNDS_SETS]={
  new BBSoundSet(7, 0, 9, true),
  new BBSoundSet(7, 9, 6, true),
  new BBSoundSet(7, 15, 6, true),
  new BBSoundSet(8, 0, 5, true),
  new BBSoundSet(8, 5, 5, true),
  new BBSoundSet(8, 10, 5, true),
  new BBSoundSet(8, 15, 4, true),
  new BBSoundSet(8, 19, 4, true),
  new BBSoundSet(8, 23, 4, true),
  new BBSoundSet(8, 27, 4, true),
  new BBSoundSet(8, 31, 5, true),
  new BBSoundSet(10, 0, 4, true)
};

// static const int NUM_SOUNDS_SETS = 2;
// static BBSoundSet *g_soundSets[NUM_SOUNDS_SETS]={
//   new BBSoundSet(7, 0, 2, true),
//   new BBSoundSet(7, 0, 2, true),
// };


#endif