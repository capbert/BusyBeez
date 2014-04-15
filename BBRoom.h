#ifndef BB_ROOM_H
#define BB_ROOM_H

#include "Observer.h"
class BBSample;

class BBRoom : public Observer
{
public:
  


  enum RoomState {
    ROOM_STATE_ACTIVE,
    ROOM_STATE_INACTIVE
  };


  typedef void (*RoomUpdateCallback)(RoomState);


  BBRoom();
  BBRoom(BBSample *samples, int numSamples);
  // ~BBRoom();
  RoomState getState();
  void setState(RoomState);
  void update(Subject *subject);

  void setStateChangeCallback(RoomUpdateCallback);

private:
  RoomState _state;
  BBSample *p_samples;
  int _numSamples;
  RoomUpdateCallback _stateChangeCallback;
  void deactivateRoom();
  void activateRoom();
  void triggerRoomAmbienceOn();
  void triggerRoomAmbienceOff();

};


#endif // BB_ROOM_H