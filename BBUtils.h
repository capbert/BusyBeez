#ifndef BBUtils_h
#define BBUtils_h

#define SUPPRESS_SERIAL_PRINT false

#define printf(val) if(!SUPPRESS_SERIAL_PRINT) Serial.println(F(val))
#define print(val) if(!SUPPRESS_SERIAL_PRINT) Serial.println(val)

#endif // BBUtils_h




