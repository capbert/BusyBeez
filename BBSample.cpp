#include <Arduino.h>
#include <MIDI.h>
#include <assert.h>

#include "BBSample.h"
#include "BBUtils.h"

BBSample::BBSample(){
  // Empty
}

BBSample::BBSample(int ch, int note):
  _note(note),
  _channel(ch)
{
  // Empty
}



// void BBSample::setVolume(int volume){
//   assert(volume >= 0 && volume < 128); // valid MIDI values
//   int volNote = _output + VOLUME_CONTROL_NOTE_OFFSET;
//   MIDI.sendControlChange( volNote, volume, _channel);
// }

void BBSample::assignToOutput(int output){
  assert(output >= 0 && output<NUMBER_OF_PLAYBACK_OUTPUTS);
  LOGS("set output:");
  LOG(output);
  _output = output;

  for (int i = 0; i < NUMBER_OF_PLAYBACK_OUTPUTS; ++i)
  {
    int outNote = i+VOLUME_CONTROL_NOTE_OFFSET;
    (i==output) ? MIDI.sendControlChange(outNote, 127, _channel) : MIDI.sendControlChange(outNote, 0, _channel);
  }
}


void BBSample::triggerOn(bool fadeIn){
  // LOGS("sample on");
  // LOG(_channel);

  _startMillis = millis();
  if(fadeIn)
    MIDI.sendNoteOn(FADE_IN_NOTE, 127, _channel);
  MIDI.sendNoteOn(_note, 127, _channel);
}

void BBSample::triggerOff(bool fadeOut){

  // LOGS("sample off");
  // LOG(_channel);
  if(fadeOut)
    MIDI.sendNoteOn(FADE_OUT_NOTE, 127, _channel);
  else
    MIDI.sendNoteOn(_note, 0, _channel);


}