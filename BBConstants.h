
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"
#include "EZSensor.h"
#include "PIRSensor.h"



static const byte RX_PIN = 8;

// =========================== Sensors ===========================

static const int NUM_ROOM_SENSORS = 3;
static BBSensor *g_RoomSensors[NUM_ROOM_SENSORS] = {
  new PIRSensor(2),
  new PIRSensor(3),
  new PIRSensor(4)
};

static const int NUM_FLOWERS = 6;
static EZSensor *g_FlowerSensors[NUM_FLOWERS] = {
  new EZSensor(A0),
  new EZSensor(A1),
  new EZSensor(A2),
  new EZSensor(A3),
  new EZSensor(A4),
  new EZSensor(A5)
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
  new BBFlower(5, 2)
  };


#endif