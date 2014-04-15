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

BBSample::BBSample(int ch, int note, String name, int delay){
  _note = note;
  _velocity = 127;
  _channel = ch;
  _name = name;
  _delay = delay;
}

void BBSample::triggerOn(){
  printf("trigger sample on");
  print(_channel);

  _startMillis = millis();
  MIDI.sendNoteOn(_note, _velocity, _channel);
}

void BBSample::triggerOff(){

  printf("trigger sample off");
  print(_channel);
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