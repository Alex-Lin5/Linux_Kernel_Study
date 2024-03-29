// exception.cc
//  Entry point into the Nachos kernel from user programs.
//  There are two kinds of things that can cause control to
//  transfer back to here from user code:
//
//  syscall -- The user code explicitly requests to call a procedure
//  in the Nachos kernel.  Right now, the only function we support is
//  "Halt".
//
//  exceptions -- The user code does something that the CPU can't handle.
//  For instance, accessing memory that doesn't exist, arithmetic errors,
//  etc.
//
//  Interrupts (which can also cause control to transfer from user
//  code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
//  Entry point into the Nachos kernel.  Called when a user program
//  is executing, and either does a syscall, or generates an addressing
//  or arithmetic exception.
//
//  For system calls, the following is the calling convention:
//
//  system call code -- r2
//    arg1 -- r4
//    arg2 -- r5
//    arg3 -- r6
//    arg4 -- r7
//
//  The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//  "which" is the kind of exception.  The list of possible exceptions
//  is in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);
  int result;
  int temp;
	  int adr, size, fd;
  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");
  
  switch (which) {
    case SyscallException:
      switch(type) {
        case SC_Halt:
          DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
          
          SysHalt();
          break;
          
        case SC_Add:
          DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
          
          /* Process SysAdd Systemcall*/
          result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
                          /* int op2 */(int)kernel->machine->ReadRegister(5));
          
          DEBUG(dbgSys, "Add returning with " << result << "\n");
          /* Prepare Result */
          kernel->machine->WriteRegister(2, (int)result);
          
          
          break;


        case SC_Exit:
          //printf("Exit system call made by %s\n", kernel->currentThread->getName());
          
          DEBUG(dbgSys, "Exit " << kernel->machine->ReadRegister(4) << "\n");
          
          // Extract exit status 
          temp = kernel->machine->ReadRegister(4); 
          if(temp == 0)
            printf("Process exited normally\n");
          else
            cout << "Process exited abnormally with status " << temp << endl;

          
          // Let's finish this thread
          kernel->currentThread->Finish();
          break;
         


          /*======================================
           * TODO: Finish the implementations
           * for the following system calls
           * ====================================
           */
        case SC_Read:
          printf("Read system call made by %s\n", kernel->currentThread->getName());
          
	  adr = kernel->machine->ReadRegister(4);
	  size = kernel->machine->ReadRegister(5);
	  fd = kernel->machine->ReadRegister(6);
	  result = SysRead(adr, size, fd);

	  if(result == -1){
	    printf("Read() system call fail\n");
	  }
	  kernel->machine->WriteRegister(2, (int)result);
	  printf("Read() returned %d\n", result);

          break;

          
        case SC_Write:
          // printf("Write system call made by %s\n", kernel->currentThread->getName());
	  adr = kernel->machine->ReadRegister(4);
	  size = kernel->machine->ReadRegister(5);
	  fd = kernel->machine->ReadRegister(6);
	  result = SysWrite(adr, size, fd);

	  if(result == -1){
	    printf("Write() system call fail\n");
	  }
	  kernel->machine->WriteRegister(2, (int)result);
	  // printf("Write() returned %d\n", result);
          

          break;


      
        case SC_Create:
          printf("Create() system call is called by %s\n", kernel->currentThread->getName());
	  result = SysCreate(kernel->machine->ReadRegister(4)); // Create(char *name)
	  if(result == 1){
	    printf("Create() system call success\n");
	  } else if(result == -1){
	    printf("Create() system call fail\n");
	  }


	  kernel->machine->WriteRegister(2, (int)result);
	  printf("Create() returned %d\n", result);
          break;



        case SC_Open:
          adr = kernel->machine->ReadRegister(4); 
          printf("Open() system call is called by %x\n", adr);
	  result = SysOpen(adr); // Open(char *name)
                    
	  if(result == -1){
	    printf("Open() system call fail\n");
	  }
	  kernel->machine->WriteRegister(2, (int)result);
	  printf("Open() returned %d\n", result);
          break;




        case SC_Close:
          fd = kernel->machine->ReadRegister(4); 
          printf("Close() system call is called by %d\n", fd);
          result = SysClose(fd); 
	  kernel->machine->WriteRegister(2, (int)result);
	  printf("Close() returned %d\n", result);
          break;



          // NOT REQUIRED FOR THIS PA
        case SC_Exec:
          printf("Exec() system call is called\n");
          break;


        case SC_Join:
          printf("Join() system call is called\n");
          break;


        default:
          cerr << "Unexpected system call " << type << "\n";
          break;
      }
      break;
    default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      break;
  }
  
  /* Modify return point */
  {
    /* set previous programm counter (debugging only)*/
    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
    
    /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
    
    /* set next programm counter for brach execution */
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
  }
}
