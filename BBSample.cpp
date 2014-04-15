#include <Arduino.h>
#include <MIDI.h>
// #include <midi_Defs.h>
// #include <midi_Namespace.h>
// #include <midi_Settings.h>

#include "SimpleTimer.h"

#include "BBSample.h"
#include "BBUtils.h"

const int BBSample::FADE_IN_NOTE = 58;
const int BBSample::FADE_OUT_NOTE = 60;

BBSample::BBSample(){
  // Empty
}

BBSample::BBSample(int ch, int note, String name, int delay){
  _note = note;
  _velocity = 127;
  _channel = ch;
  _name = name;
  _delay = delay;
}

void BBSample::triggerOn(bool fadeIn){
  printf("trigger sample on");
  print(_channel);

  _startMillis = millis();
  if(fadeIn)
    MIDI.sendNoteOn(FADE_IN_NOTE, _velocity, _channel);
  MIDI.sendNoteOn(_note, _velocity, _channel);
}

void BBSample::triggerOff(bool fadeOut){

  printf("trigger sample off");
  print(_channel);
  if(fadeOut)
    MIDI.sendNoteOn(FADE_OUT_NOTE, _velocity, _channel);
  else
    MIDI.sendNoteOn(_note, 0, _channel);

}

String BBSample::description(){
  return String(_name + ": ch: " + String(_channel) + " note: "+ String(_note));
}

bool BBSample::canRetrigger(){
  
  static int lastMillis;
  
  int mils = millis();
  int elapsedMillis =  mils - _startMillis;

  if ( elapsedMillis > _delay ){
    _startMillis = mils;
    return true;
  } 

  return false;

}