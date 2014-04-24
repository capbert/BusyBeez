
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"


// =========================== Constants ===========================
static const int NUM_FLOWER_SAMPLES = 12;





// =========================== Samples ===========================
static BBSample g_FlowerSamples[NUM_FLOWER_SAMPLES] = {
  BBSample(1, 0),
  BBSample(2, 0),
  BBSample(3, 0),
  BBSample(4, 0),
  BBSample(5, 0),
  BBSample(6, 0),
  BBSample(7, 0),
  BBSample(8, 0),
  BBSample(9, 0),
  BBSample(10, 0),
  BBSample(11, 0),
  BBSample(12, 0)
};

static BBSample g_FlowerSampleGroup01[2] = {
  g_FlowerSamples[0],
  g_FlowerSamples[1],
};

static BBSample g_FlowerSampleGroup02[2] = {
  g_FlowerSamples[2],
  g_FlowerSamples[3],
};

static BBSample g_FlowerSampleGroup03[2] = {
  g_FlowerSamples[4],
  g_FlowerSamples[5],
};

static BBSample g_FlowerSampleGroup04[3] = {
  g_FlowerSamples[6],
  g_FlowerSamples[7],
  g_FlowerSamples[8],
};

static BBSample g_FlowerSampleGroup05[3] = {
  g_FlowerSamples[9],
  g_FlowerSamples[10],
  g_FlowerSamples[11],
};

static const int NUM_AMBIENCE_SAMPLES = 1;

static BBSample g_AmbienceSamples[NUM_AMBIENCE_SAMPLES] = {
  BBSample(16, 0),
};

// =========================== End Samples ===========================





// =========================== Sensors ===========================

static BBSensor g_RoomMotionSensor(BBSensor::DIGITAL, 2);


static BBRoom g_Room(g_AmbienceSamples, NUM_AMBIENCE_SAMPLES);



static const int NUM_FLOWERS = 5;


static BBSensor g_FlowerSensors[NUM_FLOWERS] = {
  BBSensor(BBSensor::ANALOG, A0),
  BBSensor(BBSensor::ANALOG, A1),
  BBSensor(BBSensor::ANALOG, A2),
  BBSensor(BBSensor::ANALOG, A3),
  // BBSensor(BBSensor::ANALOG, A4),
  BBSensor(BBSensor::ANALOG, A5, true),
};


// =========================== End Sensors ===========================



// =========================== Flowers ===========================


static BBFlower g_Flowers[NUM_FLOWERS] = {
  BBFlower(g_FlowerSampleGroup01, 2, 1),
  BBFlower(g_FlowerSampleGroup02, 2, 1),
  BBFlower(g_FlowerSampleGroup03, 2, 1),
  BBFlower(g_FlowerSampleGroup04, 2, 1),
  BBFlower(g_FlowerSampleGroup05, 2, 1),
  // BBFlower(g_FlowerSampleGroup06, 2, 1),
  };


// =========================== End Flowers ===========================



#endif