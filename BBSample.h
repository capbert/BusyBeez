#include <Arduino.h>

#ifndef BBSample_h
#define BBSample_h


class BBSample {
private:

  int _note;
  int _velocity;
  int _channel;
  String _name;
  int _delay;
  int _startMillis;

public:
  BBSample();
  BBSample(int ch, int note, String name, int delay = 5000);
  void triggerOn();
  void triggerOff();
  String description();
  bool canRetrigger();



};

#endif