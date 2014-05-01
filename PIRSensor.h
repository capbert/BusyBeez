#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include "BBSensor.h"

class PIRSensor: public BBSensor {
private:

  int readSensor(); 

public:
  PIRSensor(int);

  void begin();

protected:
  
  // Override
  // int readSensor(); 
  int  _sensorType;
};

#endif // PIR_SENSOR_H