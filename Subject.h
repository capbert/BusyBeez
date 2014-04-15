#ifndef SUBJECT_H
#define SUBJECT_H
#include "StandardCplusplus.h"
#include "vector"

class Subject
{

  private:
    std::vector<class Observer *> _observers;

  public:
    

    Subject();
    // ~Subject();


    void attach(Observer *observer);
    void detatch(Observer *observer);

    void notify();

};

#endif // SUBJECT_H