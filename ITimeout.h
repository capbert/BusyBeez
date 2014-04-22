#ifndef I_TIMEOUT_H
#define I_TIMEOUT_H

class ITimeout
{
public:
  void setTimeout(int);

protected:
  int _timeout;
  bool timeoutHasExpired();
  void updateTimeout();
  virtual void handleTimeout();
  void resetTimeout();
  
private: 
  unsigned long _timeoutStart;
  unsigned long getElapsedTime();
  void startTimeout(); 
};


#endif // I_TIMEOUT_H