
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"
#include "BBSensor.h"
#include "EZSensor.h"
#include "PIRSensor.h"
#include "BBSoundSetPool.h"


static const byte TX_PIN = 7;
static const byte RX_PIN = 8;

// =========================== Sensors ===========================

static const int NUM_ROOM_SENSORS = 3;
static BBSensor *g_RoomSensors[NUM_ROOM_SENSORS] = {
  new PIRSensor(2),
  new PIRSensor(3),
  new PIRSensor(4)
};

static const int NUM_FLOWERS = 5;
static EZSensor *g_FlowerSensors[NUM_FLOWERS] = {
  new EZSensor(A0),
  new EZSensor(A1),
  new EZSensor(A2),
  new EZSensor(A3),
  new EZSensor(A4),
  // new EZSensor(A5)
};

static SensorDescription sConfig[NUM_FLOWERS] = {
  {BBSensor::EZ, {24,200}, {0,127}},
  {BBSensor::EZ, {24,300}, {0,127}},
  {BBSensor::EZ, {24,400}, {0,127}},
  {BBSensor::EZ, {24,500}, {0,127}},
  {BBSensor::EZ, {24,600}, {0,127}},
  // {BBSensor::EZ,{24,200}, {0,127}}
};

// =========================== Room ===========================

static const int NUM_AMBIENCE_SAMPLES = 1;
static BBRoom g_Room(NUM_AMBIENCE_SAMPLES);



// =========================== Flowers ===========================


static BBFlower *g_Flowers[NUM_FLOWERS] = {
  new BBFlower(0, 2),
  new BBFlower(1, 2),
  new BBFlower(2, 2),
  new BBFlower(3, 2),
  new BBFlower(4, 2),
  // new BBFlower(5, 2)
  };


// =========================== Flowers ===========================

static BBSoundSetPool *g_soundSetPool = BBSoundSetPool::getInstance();

#endif