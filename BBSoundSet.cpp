// #include <Arduino.h>
#include "BBSoundSet.h"
#include "BBUtils.h"

#include <algorithm>
#include <MIDI.h>
#include "BBSensor.h"

BBSoundSet::BBSoundSet(int channel, int startNote, int numSounds, bool shuffle ):
_channel(channel),
_startNote(startNote),
_numSounds(numSounds),
_shuffle(shuffle)
{
  // createPlaylist(_numSounds);
  reset();
}

void BBSoundSet::update(ISubject *subject){
// LOGS("-------update");

/*

when triggertime expires 
  reset triggertime
  start capturing sensor readings
when capture period expires 
  do something with the values
  trigger sample


  _


*/
  if(_captureReadings){
    // LOGS("-- capture --");
    // LOG(_numReadings);
    int sensorValue = ((BBSensor*)subject)->read();
    _runningTotal += sensorValue;
    _numReadings++;

    if(_numReadings == 7){
      // LOGS("--- END CAPTURE ---");
      _captureReadings = false;
      _numReadings = 0;
      _runningTotal = 0;

      int x = rand()%128;
      int y = rand()%128;
      
      int average = _runningTotal / (_numReadings - 1); //TODO: fix this -1

      // _runningTotal = 0; // TODO: reset totalm
      // _numReadings =0;
      resetTriggerTime();
      triggerSound(_currentIndex + _startNote);
      setAmbience(average);
      pan3D(x,y);
      
      _currentIndex ++;

      if(_currentIndex == _numSounds){
        _currentIndex = 0;
        _done = true;
      } 


    }
  }
  int shouldTrigger = millis() % _triggerTime;
  if(shouldTrigger < 50 ){ 
    // LOGS("--- BEGIN CAPTURE ---");
    // LOG(shouldTrigger);
    _captureReadings = true;
  // TODO: 110 is a slop value and is tied to the refresh rate. not sure what to do about this. be careful.


    // int avg = _runningTotal/_numReadings;

    // // int sensorValue = avg;
    // int sensorValue = 64;
    // // int triggerNote = rand() % _numSounds;
    // int x = rand()%128;
    // int y = rand()%128;
    


    // // _runningTotal = 0; // TODO: reset totalm
    // // _numReadings =0;
    // resetTriggerTime();
    // triggerSound(_currentIndex + _startNote);
    // setAmbience(sensorValue);
    // pan3D(x,y);
    
    // _currentIndex ++;

    // if(_currentIndex == _numSounds){
    //   _currentIndex = 0;
    //   _done = true;
    // } 

  }
}






void BBSoundSet::resetTriggerTime(){
  _triggerTime = rand() % (MAX_TRIGGER_TIME - MIN_TRIGGER_TIME) + MIN_TRIGGER_TIME;

}

void BBSoundSet::reset(){
  resetTriggerTime();
  _captureReadings = false;
  _runningTotal = 0;
  _numReadings =0;
  _currentIndex = 0;
  _done = false;
}

bool BBSoundSet::done(){
  // LOG(_done);
  if(_done) {
    LOGS("----- DONE -----");
  }
  return _done;
}


// void BBSoundSet::createPlaylist(int length){
//   for (int i = 0; i < length; ++i) _playlist.push_back(i);
//   shuffle(&_playlist);
//   LOGS("---------");
//   for(int i=0; i<_playlist.size(); i++){
//       LOG(_playlist.at(i));
//       // LOGS(", ");
//   }
// }

// void BBSoundSet::shuffle(std::vector<int> *vec){
//   LOGS("BBSoundSet::shuffle");
//   std::random_shuffle(vec->begin(), vec->end()+1); // shuffle STL containerstd
// }

void BBSoundSet::triggerSound(int note){
  LOGS("BBSoundSet::triggerSound()");
  LOG(note);

  MIDI.sendNoteOn(note, 127, _channel);

}


// TODO: this should be abstracted
void BBSoundSet::pan3D(int x, int y){
  MIDI.sendControlChange(0, x, MIDI_PAN_CHANNEL); // send X
  MIDI.sendControlChange(1, y, MIDI_PAN_CHANNEL); // send Y
  LOGS("BBSoundSet::pan3D()");
}

void BBSoundSet::setAmbience(int val){
  MIDI.sendControlChange(2,val,_channel);
  LOGS("BBSoundSet::setAmbience()");
}