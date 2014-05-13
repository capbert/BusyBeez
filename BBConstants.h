
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"
#include "BBSensor.h"
#include "EZSensor.h"
#include "PIRSensor.h"
#include "BBSoundSetPool.h"
#include "BBSoundSet.h"


static const int NUM_FLOWERS = 6;


static const int TRIGGER_PIN = 13;
static const int SENSOR_REFRESH_RATE = 60 * NUM_FLOWERS;


static const unsigned int MIN_SET_TRIGGER_TIME = 30000;
static const unsigned int MAX_SET_TRIGGER_TIME = 65000;

static const unsigned int MIN_MISC_SOUND_TRIGGER_TIME = 15000;
static const unsigned int MAX_MISC_SOUND_TRIGGER_TIME = 65000;

static const unsigned int MAX_MISC_SOUND_TIMEOUT = 20000;
static const int FADE_TIME = 2500;

// static const unsigned int MIN_SET_TRIGGER_TIME = 2000;
// static const unsigned int MAX_SET_TRIGGER_TIME = 400;

// static const unsigned int MIN_MISC_SOUND_TRIGGER_TIME = 2000;
// static const unsigned int MAX_MISC_SOUND_TRIGGER_TIME = 4000;

// static const unsigned int MAX_MISC_SOUND_TIMEOUT = 1000;
// static const int FADE_TIME = 250;

// =========================== Sensors ===========================

static const int NUM_ROOM_SENSORS = 3;

static BBSensor *g_RoomSensors[NUM_ROOM_SENSORS] = {
  BBSensor::create((SensorDescription){ BBSensor::PIR, 2, {0,1}, {0,1} }),
  BBSensor::create((SensorDescription){ BBSensor::PIR, 3, {0,1}, {0,1} }),
  BBSensor::create((SensorDescription){ BBSensor::PIR, 4, {0,1}, {0,1} })
};




// =========================== Room ===========================

static const int NUM_AMBIENCE_SAMPLES = 1;
static BBRoom g_Room(NUM_AMBIENCE_SAMPLES);



// =========================== Flowers ===========================





static BBSensor *g_FlowerSensors[NUM_FLOWERS] = {

  BBSensor::create((SensorDescription){BBSensor::EZ, A0, {12,144}, {0,127}}),
  BBSensor::create((SensorDescription){BBSensor::EZ, A1, {12,144}, {0,127}}),
  BBSensor::create((SensorDescription){BBSensor::EZ, A2, {12,144}, {0,127}}),
  BBSensor::create((SensorDescription){BBSensor::EZ, A3, {12,144}, {0,127}}),
  BBSensor::create((SensorDescription){BBSensor::EZ, A4, {12,144}, {0,127}}),
  BBSensor::create((SensorDescription){BBSensor::EZ, A5, {12,120}, {0,127}})

};


static BBFlower *g_Flowers[NUM_FLOWERS] = {

  new BBFlower(0, 7),
  new BBFlower(1, 7),
  new BBFlower(2, 7),
  new BBFlower(3, 7),
  new BBFlower(4, 7),
  new BBFlower(5, 7)

};


// =========================== Sound Sets ===========================

static BBSoundSet* currentSoundSet;
static BBSoundSetPool *g_soundSetPool = BBSoundSetPool::getInstance();


static const int NUM_SOUNDS_SETS = 12;
static BBSoundSet *g_soundSets[NUM_SOUNDS_SETS]={
  new BBSoundSet(7, 0, 5, true),
  new BBSoundSet(7, 5, 5, true),
  
  new BBSoundSet(8, 0, 5, true),
  new BBSoundSet(8, 5, 5, true),

  new BBSoundSet(9, 0, 4, true),
  new BBSoundSet(9, 4, 4, true),
  new BBSoundSet(9, 8, 4, true),
  new BBSoundSet(9, 12, 4, true),

  new BBSoundSet(10, 0, 4, true),
  new BBSoundSet(10, 4, 4, true),
  new BBSoundSet(10, 8, 4, true),
  new BBSoundSet(10, 12, 4, true)
};

// static const int NUM_SOUNDS_SETS = 2;
// static BBSoundSet *g_soundSets[NUM_SOUNDS_SETS]={
//   new BBSoundSet(7, 0, 2, true),
//   new BBSoundSet(7, 0, 2, true),
// };


#endif