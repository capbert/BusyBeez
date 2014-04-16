#include <Arduino.h>
#include <MIDI.h>
// #include <midi_Defs.h>
// #include <midi_Namespace.h>
// #include <midi_Settings.h>

#include "SimpleTimer.h"

#include "BBSample.h"
#include "BBUtils.h"

BBSample::BBSample(){
  // Empty
}

BBSample::BBSample(int ch, int note):
  _note(note),
  _velocity(127),
  _channel(ch)
{
  // Empty
}

void BBSample::triggerOn(bool fadeIn){
  printf("sample on");
  print(_channel);

  _startMillis = millis();
  if(fadeIn)
    MIDI.sendNoteOn(FADE_IN_NOTE, _velocity, _channel);
  MIDI.sendNoteOn(_note, _velocity, _channel);
}

void BBSample::triggerOff(bool fadeOut){

  printf("sample off");
  print(_channel);
  if(fadeOut)
    MIDI.sendNoteOn(FADE_OUT_NOTE, _velocity, _channel);
  else
    MIDI.sendNoteOn(_note, 0, _channel);


}