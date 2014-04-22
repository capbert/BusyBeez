#ifndef BB_ROOM_H
#define BB_ROOM_H

#include "IObserver.h"
#include "ITimeout.h"

class BBSample;

class BBRoom : public IObserver, public ITimeout
{
public:
  


  enum RoomState {
    ROOM_STATE_ACTIVE,
    ROOM_STATE_INACTIVE
  };


  typedef void (*RoomUpdateCallback)(RoomState);


  // BBRoom();
  BBRoom(BBSample *samples, int numSamples);
  // ~BBRoom();
  RoomState getState();
  void setState(RoomState);
  void update(ISubject *subject);

  void setStateChangeCallback(RoomUpdateCallback);

private:
  static const int DEFAULT_TIMEOUT = 30000;
  RoomState _state;
  BBSample *p_samples;
  int _numSamples;
  RoomUpdateCallback _stateChangeCallback;

  // long _activatedTime;
  // long getElapsedTime();

  void deactivateRoom();
  void activateRoom();
  void triggerRoomAmbienceOn();
  void triggerRoomAmbienceOff();

  void handleTimeout();

};


#endif // BB_ROOM_H