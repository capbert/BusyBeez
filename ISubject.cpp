
#include "StandardCplusplus.h"
#include <vector>
#include <algorithm>

#include "ISubject.h"
#include "IObserver.h"

#include "BBUtils.h"

void ISubject::notify(){
  // printf("notify observers: ");
  // print(_observers.size());
  for(int i=0; i<_observers.size(); i++){
  // print((int)this);
    _observers[i]->update(this);
  }
}

void ISubject::attach(IObserver *observer){
  // printf("attatching Observer: ");
  // print((int)this);
  _observers.push_back(observer);
  // print(_observers.size());
}

void ISubject::detatch(IObserver *observer){
  std::vector<class IObserver *>::iterator position = std::find(_observers.begin(), _observers.end(), observer);
  if (position != _observers.end()) // == vector.end() means the element was not found
    _observers.erase(position);
}