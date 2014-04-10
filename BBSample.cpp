#include <Arduino.h>
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

#include "BBSample.h"

BBSample::BBSample(){
  // Empty
}

BBSample::BBSample(int ch, int note, String name){
  _note = note;
  _velocity = 127;
  _channel = ch;
  _name = name;
}

void BBSample::triggerOn(){
  // String str = description();
  // Serial.print(String("triggering sample: " + str));
  
  MIDI.sendNoteOn(_note, _velocity, _channel);
}

void BBSample::triggerOff(){
  MIDI.sendNoteOn(_note, 0, _channel);
}

String BBSample::description(){
  return String(_name + ": ch: " + String(_channel) + " note: "+ String(_note));
}