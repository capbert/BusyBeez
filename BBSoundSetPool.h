#ifndef BB_SOUND_SET_POOL_H
#define BB_SOUND_SET_POOL_H

// #include <vector>
#include "BBSoundSet.h"
// class BBSoundSet;

class BBSoundSetPool {
private:

  // typedef std::vector<BBSoundSet *> SetVector;
  // typedef SetVector::iterator SetIterator;

  static BBSoundSetPool * _instance;
  // static SetVector _sets;
  BBSoundSet **_sets;
  int _numSets;

  int _currentIndex;
public:
  void shuffle();

  static BBSoundSetPool *getInstance();

  BBSoundSetPool();

  // TODO: Create config structs
  // void generatePool(SoundSetDescription[], int);
  void setPool(BBSoundSet *[], int );

  BBSoundSet *getSet();
  void returnSet(BBSoundSet *);
  bool done();
  // void updateAll();
  
};


#endif // BB_SOUND_SET_POOL_H
