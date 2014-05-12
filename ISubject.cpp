
#include "StandardCplusplus.h"
#include <vector>
#include <algorithm>

#include "ISubject.h"
#include "IObserver.h"

#include "BBUtils.h"

void ISubject::notify(){
  // LOGS("notify observers: ");
  for(int i=0; i<_observers.size(); i++){
    _observers[i]->update(this);
  }
}

void ISubject::attach(IObserver *observer){
  // LOGS("attatching Observer: ");
  // LOG((int)this);

  // don't add if already subscribed
  if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
  {
    _observers.push_back(observer);
  }

}

void ISubject::detatch(IObserver *observer){

  ObserverVector::iterator position = std::find(_observers.begin(), _observers.end(), observer);
  if (position != _observers.end()) {// == vector.end() means the element was not found
    _observers.erase(position);
    // LOGS("remove observer: ");
  }

}