#include <Arduino.h>

#ifndef BBSample_h
#define BBSample_h

class BBSample {
private:

  int _note;
  int _velocity;
  int _channel;
  String _name;
public:
  BBSample();
  BBSample(int ch, int note, String name);
  void triggerOn();
  void triggerOff();
  String description();
};

#endif