#ifndef BB_SOUND_SET_H
#define BB_SOUND_SET_H

#include <Arduino.h>
#include "StandardCplusplus.h"
#include <vector>
#include "IObserver.h"


class BBSoundSet : public IObserver 
{

private:

  static const int MIN_TRIGGER_TIME = 20000;
  static const int MAX_TRIGGER_TIME = 45000;

  static const int MIDI_PAN_CHANNEL = 7;

  int _channel;
  int _startNote;
  int _numSounds;
  bool _shuffle;

  int _currentIndex;
  int _triggerTime;
  bool _done;

  unsigned int _runningTotal;
  unsigned int _numReadings;
  bool _captureReadings;
  // unsigned long _lastTime;

  void pan3D(int x, int y);
  void triggerSound(int note);
  void setAmbience(int val);
  void resetTriggerTime();


public:

  BBSoundSet(int channel, int startNote, int numSounds, bool shuffle );
  void update(ISubject *);
  bool done(); //TODO: in lieu of a callback poll to see if all have played
  void reset();
  void test();
};

struct SoundSetDescription {
  byte channel;
  byte startNote;
  byte numSounds;
  bool shuffle;
};

#endif // BB_SOUND_SET_H
