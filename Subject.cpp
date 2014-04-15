
#include "StandardCplusplus.h"
#include <vector>
#include <algorithm>

#include "Subject.h"
#include "Observer.h"

#include "BBUtils.h"

Subject::Subject(){

}

void Subject::notify(){
  // printf("notify observers: ");
  // print(_observers.size());
  for(int i=0; i<_observers.size(); i++){
  // print((int)this);
    _observers[i]->update(this);
  }
}

void Subject::attach(Observer *observer){
  // printf("attatching Observer: ");
  // print((int)this);
  _observers.push_back(observer);
  // print(_observers.size());
}

void Subject::detatch(Observer *observer){
  std::vector<class Observer *>::iterator position = std::find(_observers.begin(), _observers.end(), observer);
  if (position != _observers.end()) // == vector.end() means the element was not found
    _observers.erase(position);
}