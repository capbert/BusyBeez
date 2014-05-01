#ifndef ISUBJECT_H
#define ISUBJECT_H
#include "StandardCplusplus.h"
#include "vector"

class IObserver; 

class ISubject
{

  private:
    std::vector<class IObserver *> _observers;

  public:
    

    // Subject();
    // ~Subject();


    void attach(IObserver *observer);
    void detatch(IObserver *observer);
    void notify();
    

};

#endif // ISUBJECT_H