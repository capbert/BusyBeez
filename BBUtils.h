#ifndef BBUtils_h
#define BBUtils_h

#define SUPPRESS_SERIAL_PRINT false
#include <Arduino.h>

#define SUPPRESS_SERIAL_PRINT true
#define printf(val) if(!SUPPRESS_SERIAL_PRINT) Serial.println(F(val))
#define print(val) if(!SUPPRESS_SERIAL_PRINT) Serial.println(val)

#endif // BBUtils_h




