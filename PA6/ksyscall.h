/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// #include <stdio.h>
#define FILENAME_LEN 128
int getMemStr(int addr, int size, int* strpt){
    char *str = new char[FILENAME_LEN];
    *strpt = (int) str;
    int ch, i;
    if(size == -1) size = FILENAME_LEN;
    for (i = 0; i < size; i++)
    {
      // read 1 byte from memory
      if (kernel->machine->ReadMem(addr+i, 1, &ch) == FALSE)
      {
        DEBUG(dbgSys, "Machine::ReadMem returned false.\n");
        return i;
      }
      str[i] = (char) ch;
      if(str[i] == '\0') break;
    }
    // printf("String in getMemStr is %s\n", str);
    return i;

}

void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}


/**
 * Syswrite - the internal Write system call 
 * @param 
 *  addr - read from this address
 *  size - read this amount of bytes
 *  fp   - write to this file descriptor
 */
int SysWrite(int addr, int size, int fp)
{
  int rd;
    int str;
    rd = getMemStr(addr, size, &str);
  if(rd <= 0){
    printf("Get invalid character\n");
    return -1;
  }
  if (fp == ConsoleOutput)
  {

    printf("%s", (char *)str);
  }
  else if(fp <= 0){
    cout << "Unsupported file descriptor" << endl;
    return -1;
  } else{
    rd = write(fp, (void *)str, size);
    if(rd == -1){
      printf("Write error on fp %d\n", fp);
      return -1;
    }
  }

  return rd; /* either -1 or bytes written so far */
}

int SysCreate(int adrname){
  int str, rc, fd;
  char * filename;
  rc = getMemStr(adrname, -1, &str);
  if(rc <= 0){
    printf("Get invalid character\n");
    return -1;
  }
  filename = (char *) str;
  // printf("Filename created is %s\n", filename);
  // fd = open(filename, O_CREAT|O_RDONLY);
  fd = open(filename, O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
  if(fd == -1){
    printf("File created in failue\n");
    return -1;
  }
  else{
    // for (int i=0; i<10000; i++);
    printf("File is created successfully, fd is %d.\n", fd);
    rc = close(fd);
  }
  if(rc == -1){
    printf("Close error.\n");
    return -1;
  } else if(rc == 0){
    printf("Close success in %d.\n", fd);
  }
  // for (int i=0; i<100000; i++);
  return 1; // file create success

}

OpenFileId SysOpen(int adrname){
  int str, rc, fd;
  char * filename;
  rc = getMemStr(adrname, -1, &str);
  filename = (char *) str;
  if(rc <= 0){
    printf("Get invalid character\n");
    return -1;
  }
  fd = open(filename, O_RDWR);
  if(fd == -1){
    printf("File open in failue\n");
    return -1;
  }

  for (int i=0; i<10000; i++);
  return fd;
}

int SysClose(OpenFileId fid){
  int rc;
  rc = close(fid);
    if(rc == -1){
      printf("close file error. File id is %d\n", fid);
      return -1;
    }
    return 1;
}


int SysRead(int adrread, int size, int openfd){
  #define BIG_LEN 3000
  int rc, fp;
  char str[BIG_LEN];
  fp = openfd;
  if (fp == ConsoleInput)
  {

    printf("Read from Console input\n");
  }
  else if(fp <= 0){
    cout << "Unsupported file descriptor" << endl;
    return -1;
  }
    rc = read(fp, (void *)str, size);
    if(rc == -1){
      printf("Read memory error, fp=%d, bufferadr=%p\n", fp, (void *)adrread);
      return -1;
    }
    str[size] = '\0';
  // printf("String read is: %s\n", (char *)str);
  for (int i=0; i<size; i++){
      char ch = (char) str[i];
      if (kernel->machine->WriteMem(adrread+i, 1, ch) == FALSE)
      {
        DEBUG(dbgSys, "Machine::WriteMem returned false.\n");
        return i;
      }
      if(str[i] == '\0') break;
    }

  // for (int i=0; i<10000; i++);
  return rc;

}

#endif /* ! __USERPROG_KSYSCALL_H__ */
