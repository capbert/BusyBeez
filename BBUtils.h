#ifndef BBUtils_h
#define BBUtils_h

#include <Arduino.h>

// #define DEBUG

#ifdef DEBUG

  #define LOGS(val) Serial.println(F(val))
  #define LOG(val) Serial.println(val)

#else

  #define LOGS(val) do {}while(0)
  #define LOG(val) do {}while(0)

#endif



#endif // BBUtils_h




