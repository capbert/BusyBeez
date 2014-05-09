#include "BBSoundSetPool.h"
#include "BBSoundSet.h"
#include "BBUtils.h"

#include <stdlib.h>
/*
  STATIC
*/

BBSoundSetPool *BBSoundSetPool::_instance = NULL;
// BBSoundSetPool::SetVector BBSoundSetPool::_sets;

BBSoundSetPool *BBSoundSetPool::getInstance(){
  if(!_instance){
    _instance = new BBSoundSetPool();
  }
  return _instance;
}


/*
  CONSTRUCTOR

*/
BBSoundSetPool::BBSoundSetPool(){
  _currentIndex = 0;

}


/*
  PUBLIC
*/


void BBSoundSetPool::setPool(BBSoundSet *(sets[]), int count){
  _sets = sets;
  _numSets = count;
  shuffle();
  LOGS("BBSoundSetPool::setPool()");
  // LOG(_numSets);

}

// void BBSoundSetPool::generatePool(SoundSetDescription set[], int size){

//   LOGS("BBSoundSetPool::generatePool");
//   for (int i = 0; i < size; ++i)
//   {
//     LOGS("  generate pool");

//     _sets.push_back(new BBSoundSet(set[i].channel,set[i].startNote,set[i].numSounds, set[i].shuffle));
//   }

// }

void BBSoundSetPool::shuffle(){
  // LOGS("BBSoundSet::shuffle");
  std::random_shuffle(_sets, _sets + _numSets); // shuffle STL containerstd
}

BBSoundSet *BBSoundSetPool::getSet(){
  BBSoundSet *set = _sets[_currentIndex];
  set->reset();

  _currentIndex ++;
  LOGS("BBSoundSetPool::getSet()");
  LOG(_currentIndex);
  LOG(_numSets);
  if( _currentIndex == _numSets){
    LOGS("-------------- RESET SET POOL --------------");
    shuffle();
    _currentIndex = 0;
  }
  return set;
}



// void BBSoundSetPool::updateAll(){

//   for (int i= 0; i<_numSets; i++)
//   {
//     _sets.at(i)->update(NULL);
//   }




// }