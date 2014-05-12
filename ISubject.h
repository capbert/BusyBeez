#ifndef ISUBJECT_H
#define ISUBJECT_H
#include "StandardCplusplus.h"
#include "vector"

class IObserver; 

class ISubject
{

  private:

    typedef std::vector<class IObserver *> ObserverVector;
     ObserverVector _observers;

  public:
    

    // Subject();
    // ~Subject();


    void attach(IObserver *observer);
    void detatch(IObserver *observer);
    void notify();
    

};

#endif // ISUBJECT_H