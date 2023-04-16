#include "concurrent.h"

Concurrent::Concurrent(){
  ThreadCounter = 0; 
  ProgramCounter = 0;
  for(int idx=0; idx<FILENUM; idx++){
    ConTable[idx] = -1;
    idx++;
  }
}

Concurrent::~Concurrent(){  
  for(int idx=0; idx<FILENUM; idx++){
    if(ConTable[idx] == -1)
      continue;
    delete ConTable[idx]; // entry to List of threads pointed to program
  }
}

// put this thread pid in ready queue and executes the program sid, 
// and block other threads by calling Thread::Sleep()
// if the thread is already in sleep status, wake it up
int Concurrent::getLock(int pid, int sid){
  ;
}
// return from thread pid, so other threads have chance to execute
int Concurrent::releaseLock(int pid, int sid){
  ;
}
