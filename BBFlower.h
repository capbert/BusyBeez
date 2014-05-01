

// class BBSample;
// class BBSensor;

#ifndef BBFlower_h
#define BBFlower_h 


// #include "BBSample.h"
#include "BBSensor.h"
#include "IObserver.h"
#include "ITimeout.h"


// class BBFlower 
class BBFlower : public IObserver, public ITimeout
{



public:
  
  typedef enum{
    FLOWER_STATE_ACTIVE,
    FLOWER_STATE_INACTIVE,
    FLOWER_STATE_DISABLED
  } FlowerState;


  // BBFlower(BBSample *, int numSamples, int speakerID);
  BBFlower(int id, int numSamples);




  // // TODO: refactor names triggerOn, triggerOff
  void triggerSample();
  void stopSample();

  // // void setSamples(BBSample *, int numSamples);

  void update(ISubject *subject);
  
  void disable();
  void enable();

  int getID();
  void setID(int);

  FlowerState getState();
  void setState(FlowerState);

private:
  static const int DEFAULT_TIMEOUT = 5000;


  FlowerState _state;

  // BBSensor *p_sensor;

  int _numSamples;
  int _id;
  int _currentNote;
  // BBSample *p_samples; 
  // BBSample *p_currentSample;

  // int _speakerOutputID;

  
  // BBSample* getRandomSample();
  
  void handleTimeout();

};

#endif