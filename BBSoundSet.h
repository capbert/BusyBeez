#ifndef BB_SOUND_SET_H
#define BB_SOUND_SET_H

#include <Arduino.h>
#include "StandardCplusplus.h"
#include <vector>
#include "IObserver.h"


class BBSoundSet : public IObserver 
{

private:

  // static const int MIN_TRIGGER_TIME = 20000;
  // static const int MAX_TRIGGER_TIME = 45000;

  static const byte MIDI_AMBIENCE_NOTE = 2;
  static const byte MIDI_PAN_CHANNEL = 7;
  static const byte MIDI_UNITY_NOTE = 123;
  static const byte MIDI_FADE_IN_NOTE = 124;
  static const byte MIDI_FADE_OUT_NOTE = 125;

  byte _channel;
  byte _startNote;
  byte _numSounds;
  bool _shuffle;

  byte _currentIndex;
  byte _currentNote;
  // byte _triggerTime;
  bool _done;

  // unsigned int _runningTotal;
  // unsigned int _numReadinsgs;
  // bool _captureReadings;
  // unsigned long _lastTime;

  void pan3D(int x, int y);
  void triggerSound(int note);
  void setAmbience(int val);
  // void resetTriggerTime();
  void triggerFadeIn();
  void triggerFadeOut();
  void triggerUnityGain();
  void triggerSoundOff();
public:

  BBSoundSet(byte channel, byte startNote, byte numSounds, bool shuffle );
  void update(ISubject *);
  bool done(); //TODO: in lieu of a callback poll to see if all have played
  void reset();
  void triggerClip(bool fade);
  void stopClip(bool fade);
  void print();
};

// struct SoundSetDescription {
//   byte channel;
//   byte startNote;
//   byte numSounds;
//   bool shuffle;
// };

#endif // BB_SOUND_SET_H
