// #include <Arduino.h>
#include "BBSoundSet.h"
#include "BBUtils.h"

#include <algorithm>
#include <MIDI.h>
#include "BBSensor.h"

BBSoundSet::BBSoundSet(byte channel, byte startNote, byte numSounds, bool shuffle ):
_channel(channel),
_startNote(startNote),
_numSounds(numSounds),
_shuffle(shuffle)
{
  // createPlaylist(_numSounds);
  reset();
}

void BBSoundSet::update(ISubject *subject){
LOGS("-------update");
}

void BBSoundSet::reset(){
  _currentIndex = 0;
  _currentNote = 0;
  _done = false;
}

bool BBSoundSet::done(){
  if(_done) {
    LOGS("----- DONE -----");
  }
  return _done;
}


void BBSoundSet::triggerClip(bool fade){
  

  byte x = rand()%128;
  byte y = rand()%128;
  byte amb = rand()%128;

  _currentNote = _currentIndex + _startNote;
  triggerSound(_currentIndex + _startNote);
  fade ? triggerFadeIn() : triggerUnityGain();
  setAmbience(amb);
  pan3D(x,y);
  
  _currentIndex ++;

  if(_currentIndex == _numSounds){
    _currentIndex = 0;
    _done = true;
  } 

}

void BBSoundSet::stopClip(bool fade){
  LOGS ("--------------------------------");
  // LOGS("  BBSoundSet::stopClip");
  fade ? triggerFadeOut() : triggerSoundOff();
  // triggerFadeOut();
}

void BBSoundSet::triggerFadeIn(){
   // LOGS(" BBSoundSet::triggerFadeIn");
  MIDI.sendNoteOn(MIDI_FADE_IN_NOTE, 127, _channel);
}

void BBSoundSet::triggerFadeOut(){
  LOGS("  BBSoundSet::triggerFadeOut");
  MIDI.sendNoteOn(MIDI_FADE_OUT_NOTE, 127, _channel);
}

void BBSoundSet::triggerUnityGain(){
   // LOGS(" BBSoundSet::triggerUnityGain");
  MIDI.sendNoteOn(MIDI_UNITY_NOTE, 127, _channel);
}

void BBSoundSet::triggerSound(int note){
  LOGS ("--------------------------------");
  LOGS("  BBSoundSet::triggerSound()");
  LOG(note);

  MIDI.sendNoteOn(note, 127, _channel);
  // MIDI.sendNoteOn(MIDI_UNITY_NOTE, 127, _channel); 


}

void BBSoundSet::triggerSoundOff(){
  LOGS("  BBSoundSet::triggerSoundOff");
  MIDI.sendNoteOn(_currentNote, 0, _channel);
}

// TODO: this should be abstracted
void BBSoundSet::pan3D(int x, int y){
  // LOGS("BBSoundSet::pan3D()");
  MIDI.sendControlChange(0, x, MIDI_PAN_CHANNEL); // send X
  MIDI.sendControlChange(1, y, MIDI_PAN_CHANNEL); // send Y
}

void BBSoundSet::setAmbience(int val){
  // LOGS("BBSoundSet::setAmbience()");
  MIDI.sendControlChange(MIDI_AMBIENCE_NOTE,val,_channel);
}


void BBSoundSet::print(){
  LOGS("----------------------------");
  LOG(_channel);
  LOG(_startNote);
  LOG(_numSounds);
  LOGS("----------------------------");
}