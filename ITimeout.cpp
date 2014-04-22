#include "ITimeout.h"
#include "BBUtils.h"

void ITimeout::updateTimeout(){

  if(timeoutHasExpired()){
    printf("---- timeout has expired ----");
    handleTimeout();

  } else {

    startTimeout();

  }

}

void ITimeout::setTimeout(int timeout){
  _timeout = timeout;
}

bool ITimeout::timeoutHasExpired(){
  // printf("TIME: ");
  // print(_timeoutStart);
  return ( getElapsedTime() > _timeout ) ? true : false;
}

void ITimeout::startTimeout(){

  if(_timeoutStart == 0){
    _timeoutStart = millis();
  }

}

void ITimeout::resetTimeout(){
  // 0 = "off" in this case. This may be a poor asumption.
  _timeoutStart = 0;
}

unsigned long ITimeout::getElapsedTime(){
  if (_timeoutStart > 0){
    return millis() - _timeoutStart;
  }else{
    return 0;
  }
}
