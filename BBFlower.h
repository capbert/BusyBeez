

// class BBSample;
// class BBSensor;

#ifndef BBFlower_h
#define BBFlower_h 


#include "BBSample.h"
#include "BBSensor.h"
#include "IObserver.h"
#include "ITimeout.h"


class BBFlower : public IObserver, public ITimeout
{



public:
  
  enum FlowerState{
    FLOWER_STATE_ACTIVE,
    FLOWER_STATE_INACTIVE,
    FLOWER_STATE_DISABLED
  };


  // BBFlower();
  // BBFlower(BBSensor *);
  BBFlower(BBSample *, int numSamples, int speakerID);
  // BBFlower(BBSensor *, BBSample *);

  BBSample* getRandomSample();

  // TODO: refactor names triggerOn, triggerOff
  void triggerSample();

  void stopSample();

  void setSamples(BBSample *, int numSamples);

  void setSensor(BBSensor *);
  void update(ISubject *subject);
  
  void disable();
  void enable();
  void setState(FlowerState);



  // void setTimeout(int=5000);
  

private:
  static const int DEFAULT_TIMEOUT = 5000;



  BBSensor *p_sensor;
  BBSample *p_samples; 

  int _numSamples;
  // bool _enabled;
  // bool _sampleTriggered;
  BBSample *p_currentSample;
  
  int _speakerOutputID;

  // long _activatedTime;
  FlowerState _state;
  
  FlowerState getState();
  

  
  // int _timeout;
  // unsigned long _timeoutStart;
  // long getElapsedTime();
  // bool timeoutHasExpired();
  // void updateTimeout();
  void handleTimeout();
  // void resetTimeout();
  // void startTimeout();
};

#endif