

// class BBSample;
// class BBSensor;
#include "BBSample.h"
#include "BBSensor.h"

#ifndef BBFlower_h
#define BBFlower_h 

#include "Observer.h"

class BBFlower : public Observer
{

private:
  
  BBSensor *p_sensor;
  BBSample *p_samples; 

  int _numSamples;
  bool _enabled;
  bool _sampleTriggered;
  BBSample *p_currentSample;
  

public:

  BBFlower();
  // BBFlower(BBSensor *);
  BBFlower(BBSample *, int);
  // BBFlower(BBSensor *, BBSample *);

  BBSample* getRandomSample();

  // TODO: refactor names triggerOn, triggerOff
  void triggerSample();

  void stopSample();
  


  void setSamples(BBSample *, int numSamples);






  // bool addSample(BBSample sample);
  // bool removeSample(BBSample sample);

  void setSensor(BBSensor *);
  // void addSensor(BBSensor sensor);
  // void removeSensor(BBSensor sensor);
  
  void update(Subject *subject);
  
  void disable();
  void enable();
  
  bool isDisabled();
  bool isTriggered();

};

#endif