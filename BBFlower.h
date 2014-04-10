

// class BBSample;
// class BBSensor;
#include "BBSample.h"
#include "BBSensor.h"

#ifndef BBFlower_h
#define BBFlower_h 


class BBFlower {

private:
  
  BBSensor *p_sensor;
  BBSample *p_samples; 

  int _numSamples;
  bool _enabled;
  bool _sampleTriggered;
  BBSample *p_currentSample;
  
  void triggerSample();
  void stopSample();

public:

  BBFlower();
  // BBFlower(BBSensor *);
  BBFlower(BBSample *, int);
  // BBFlower(BBSensor *, BBSample *);

  BBSample* getRandomSample();

  


  void setSamples(BBSample *, int numSamples);






  // bool addSample(BBSample sample);
  // bool removeSample(BBSample sample);

  void setSensor(BBSensor *);
  // void addSensor(BBSensor sensor);
  // void removeSensor(BBSensor sensor);
  
  void update();
  
  void disable();
  void enable();
  
  bool isDisabled();

};

#endif