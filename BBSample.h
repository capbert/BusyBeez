// #include <Arduino.h>

#ifndef BBSample_h
#define BBSample_h


class BBSample {
private:

  static const int FADE_IN_NOTE = 61;
  static const int FADE_OUT_NOTE = 60;

  int _note;
  int _velocity;
  int _channel;
  int _delay;
  int _startMillis;

public:

  BBSample();
  BBSample(int ch, int note);
  void triggerOn(bool fadeIn=false);
  void triggerOff(bool fadeOut=false);

};

#endif