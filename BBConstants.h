
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"
#include "BBSensor.h"
#include "EZSensor.h"
#include "PIRSensor.h"
#include "BBSoundSetPool.h"


// static const byte TX_PIN = 7;
// static const byte RX_PIN = 8;
static const int TRIGGER_PIN = 13;

// =========================== Sensors ===========================

typedef std::vector<BBSensor *> SensorVector;
typedef std::vector<BBFlower *> FlowerVector;

static const int NUM_ROOM_SENSORS = 3;


// static SensorVector g_RoomSensorsVector;

// static BBSensor *g_RoomSensors[NUM_ROOM_SENSORS];


static SensorDescription roomConfig[NUM_ROOM_SENSORS] = {
  { BBSensor::PIR, 2, {0,1}, {0,1} },
  { BBSensor::PIR, 3, {0,1}, {0,1} },
  { BBSensor::PIR, 4, {0,1}, {0,1} }
};

// static BBSensor *g_RoomSensors[NUM_ROOM_SENSORS] = {
//   new PIRSensor(2),
//   new PIRSensor(3),
//   new PIRSensor(4)
// };

// static SensorVector g_FlowerSensorVector;

static const int NUM_FLOWERS = 6;
static BBSensor *g_FlowerSensors[NUM_FLOWERS];
// static EZSensor *g_FlowerSensors[NUM_FLOWERS] = {
//   new EZSensor(A0),
//   new EZSensor(A1),
//   new EZSensor(A2),
//   new EZSensor(A3),
//   new EZSensor(A4),
//   // new EZSensor(A5)
// };


// =========================== Room ===========================

static const int NUM_AMBIENCE_SAMPLES = 1;
static BBRoom g_Room(NUM_AMBIENCE_SAMPLES);



// =========================== Flowers ===========================

static FlowerDescription fConfig[NUM_FLOWERS] = {
  {0, 2, {BBSensor::EZ, A0, {12,40}, {0,127}}},
  {1, 2, {BBSensor::EZ, A1, {12,60}, {0,127}}},
  {2, 2, {BBSensor::EZ, A2, {12,40}, {0,127}}},
  {3, 2, {BBSensor::EZ, A3, {12,60}, {0,127}}},
  {4, 2, {BBSensor::EZ, A4, {12,60}, {0,127}}},
  {5, 2, {BBSensor::EZ, A5, {12,25}, {0,127}}},
};




// static FlowerVector g_FlowersVector;
static BBFlower *g_Flowers[NUM_FLOWERS];


// =========================== Sound Sets ===========================

// static BBSoundSetPool *g_soundSetPool = BBSoundSetPool::getInstance();

#endif