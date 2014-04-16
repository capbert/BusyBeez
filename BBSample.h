// #include <Arduino.h>

#ifndef BBSample_h
#define BBSample_h


class BBSample {
private:

  static const int FADE_IN_NOTE = 61;
  static const int FADE_OUT_NOTE = 60;
  static const int NUMBER_OF_PLAYBACK_OUTPUTS = 6;
  static const int VOLUME_CONTROL_NOTE_OFFSET = 64;

  int _note;
  // int _velocity;
  int _channel;
  int _delay;
  int _startMillis;
  int _output;

public:

  BBSample();
  BBSample(int ch, int note);
  void triggerOn(bool fadeIn=false);
  void triggerOff(bool fadeOut=false);
  void assignToOutput(int);
  // void setVolume(int);
};

#endif