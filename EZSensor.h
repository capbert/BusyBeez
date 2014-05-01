#ifndef EZ_SENSOR_H
#define EZ_SENSOR_H

#include "BBSensor.h"

class EZSensor: public BBSensor {
private:
  // void init();

  int readSensor(); 
public:
  EZSensor(int);

  
  void begin();

protected:
  
  // Override
  int  _sensorType;

};

#endif // EZ_SENSOR_H