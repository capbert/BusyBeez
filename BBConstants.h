
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"


// =========================== Constants ===========================
static const int NUM_FLOWER_SAMPLES = 7;
static const int NUM_FLOWERS = 2;
static const int NUM_AMBIENCE_SAMPLES = 2;



// =========================== Samples ===========================
static BBSample g_FlowerSamples[] = {
  BBSample(1, 13),
  BBSample(2, 13),
  BBSample(3, 13),
  BBSample(4, 13),
  BBSample(5, 13),
  BBSample(6, 13),
  BBSample(7, 13),
  BBSample(8, 13),
  BBSample(9, 13),
  BBSample(10, 13),
  BBSample(11, 13),
  BBSample(12, 13)
};

static BBSample g_FlowerSampleGroup01[] = {
  g_FlowerSamples[0],
  g_FlowerSamples[1],
  g_FlowerSamples[2],
  g_FlowerSamples[3],
  g_FlowerSamples[4],
  g_FlowerSamples[5],
};

static BBSample g_FlowerSampleGroup02[] = {
  g_FlowerSamples[6],
  g_FlowerSamples[7],
  g_FlowerSamples[8],
  g_FlowerSamples[9],
  g_FlowerSamples[10],
  g_FlowerSamples[11],
};



static BBSample g_AmbienceSamples[] = {
  BBSample(15, 13),
  BBSample(16, 13)
};

// =========================== End Samples ===========================





// =========================== Sensors ===========================

static BBSensor g_RoomMotionSensor(BBSensor::DIGITAL, 2);

static BBRoom g_Room(g_AmbienceSamples, NUM_AMBIENCE_SAMPLES);

// static BBSensor g_FlowerProximitySensor0(BBSensor::ANALOG, 0);
// static BBSensor g_FlowerProximitySensor1(BBSensor::ANALOG, 1);
// static BBSensor g_FlowerProximitySensor2(BBSensor::ANALOG, 2);
// static BBSensor g_FlowerProximitySensor3(BBSensor::ANALOG, 3);
// static BBSensor g_FlowerProximitySensor4(BBSensor::ANALOG, 4);
// static BBSensor g_FlowerProximitySensor5(BBSensor::ANALOG, 5);


static BBSensor g_FlowerSensors[] = {
  BBSensor(BBSensor::ANALOG, A0),
  BBSensor(BBSensor::ANALOG, A1)
};


// =========================== End Sensors ===========================



// =========================== Flowers ===========================

static BBFlower g_Flowers[NUM_FLOWERS] = {
  BBFlower(g_FlowerSampleGroup01, 6, 0),
  BBFlower(g_FlowerSampleGroup02, 6, 1),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES)
  };

// =========================== End Flowers ===========================



#endif