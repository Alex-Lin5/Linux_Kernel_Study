#ifndef CONCURRENT_H
#define CONCURRENT_H

#include "list.h"
#define FILENUM = 32
class Concurrent{
  public:
    Concurrent();
    ~Concurrent();
    // counter variable in global to initialize tid and pid
    int getThreadNo() { return ThreadCounter++;}
    int getProgramNo() { return ProgramCounter++;}
    // join or remove thread to or from single program
    int addThreadIn(int sid, int pid);
    int rmThreadOut(int sid, int pid);
    List<int>* getThreadsIn(int sid); // get all threads executing the program
    int getProIDfrom(int pid); // get sid or program ID from thread or tid
    // Multi-threading concurrency, lock number is required from address space object
    int getLock(int pid, int sid);
    int releaseLock(int pid, int sid);
  private:
    int ThreadCounter;
    int ProgramCounter;
    // ConTable[List<int>*], address of each program that holds multi-threading
    int ConTable[FILENUM]; 
    
};
#endif