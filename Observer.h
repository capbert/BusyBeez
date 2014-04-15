
#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer
{
  private:
    Subject *_subject;
  
  public:
    Observer();
    // ~Observer();

    virtual void update(Subject *subject);
   
  

};

#endif // OBSERVER_H