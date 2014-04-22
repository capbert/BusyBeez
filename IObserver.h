
#ifndef IOBSERVER_H
#define IOBSERVER_H

class ISubject;

class IObserver
{
  private:
    ISubject *_subject;
  
  public:
    // Observer();
    // ~Observer();

    virtual void update(ISubject *subject);
   
  

};

#endif // IOBSERVER_H