#ifndef BBUtils_h
#define BBUtils_h

#include <Arduino.h>

// #define ALLOW_SERIAL_PRINT

#ifdef ALLOW_SERIAL_PRINT

  #define printf(val) Serial.println(F(val))
  #define print(val) Serial.println(val)

#else

  #define printf(val) do {}while(0)
  #define print(val) do {}while(0)

#endif



#endif // BBUtils_h




