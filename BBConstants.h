
#ifndef BBConstants_h
#define BBConstants_h 

#include "BBRoom.h"


// =========================== Constants ===========================
static const int NUM_FLOWER_SAMPLES = 7;
static const int NUM_FLOWERS = 2;
static const int NUM_AMBIENCE_SAMPLES = 2;



// =========================== Samples ===========================
static BBSample g_FlowerSamples[] = {
  BBSample(1, 12, "Red Wing Blackbird"),
  BBSample(2, 13, "Mourning Dove"),
  BBSample(3, 14, "Black Throated Green Warbler"),
  BBSample(4, 15, "Bluebird"),
  BBSample(5, 16, "Robin"),
  BBSample(6, 17, "Catbird"),
  BBSample(7, 18, "GoldFinch"),
  BBSample(8, 19, "White Throated Sparrow"),
  BBSample(9, 20, "Yellow Throated Warbler"),
  BBSample(10, 21, "Black Throated Blue Warbler"),
  BBSample(11, 22, "Nashville Warbler"),
  BBSample(12, 23, "Phoebe")
};

static BBSample g_AmbienceSamples[] = {
  BBSample(15, 24, "Field", 10000),
  BBSample(16, 25, "Bees", 10000)
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
  BBSensor(BBSensor::ANALOG, A1),
  BBSensor(BBSensor::ANALOG, 2),
  BBSensor(BBSensor::ANALOG, 3),
  BBSensor(BBSensor::ANALOG, 4),
  BBSensor(BBSensor::ANALOG, 5)
};


// =========================== End Sensors ===========================



// =========================== Flowers ===========================

static BBFlower g_Flowers[NUM_FLOWERS] = {
  BBFlower(g_FlowerSamples, NUM_FLOWER_SAMPLES),
  BBFlower(g_FlowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES),
  // BBFlower(g_flowerSamples, NUM_FLOWER_SAMPLES)
  };

// =========================== End Flowers ===========================



#endif