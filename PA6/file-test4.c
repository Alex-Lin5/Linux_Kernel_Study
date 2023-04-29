
#include "syscall.h"
// #include <stdio.h>
// convert an integer to a string. The code is available over the Internet
int tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
  return len+1;
}
 

int
main()
{
  OpenFileId outfile0; 

 char* str = "Hello from file-test4\n";
 char num2stringBuffer[100];
 char readBuffer[100];
 // char *readBuffer = new char[100];
 int i,j, rc;
 int numWritten = 0;
 int length = 0;
 char * temp;

  if (Create("file-test4.txt") == -1) {
     Exit(1);
  }

  outfile0 = Open("file-test4.txt");
    numWritten = Write(str, 22, outfile0);
    if(numWritten == -1) Exit(1);
    Write(str, 22, ConsoleOutput);
    Close(outfile0);
  outfile0 = Open("file-test4.txt");


    // success case
    numWritten = Read((char *)&readBuffer, 22, outfile0);
    if(numWritten >= 0){
	// printf("Read(): Successful: read %d bytes\n", numWritten);
	temp = "Read(): Successful: read ";
	Write(temp, 100, ConsoleOutput);
	// num2stringBuffer
    length = tostring(&num2stringBuffer, numWritten);
    Write(&num2stringBuffer, length, ConsoleOutput);
    temp = " bytes\n";
	    Write(temp, 100, ConsoleOutput);
    }
    else Exit(1);
    rc = Close(outfile0);
    if(rc != -1) {
	// printf("Close(): Successful: returned %d\n", rc);
	temp = "Close(): Successful: returned ";
	    Write(temp, 100, ConsoleOutput);
    length = tostring(&num2stringBuffer, rc);
    Write(&num2stringBuffer, length, ConsoleOutput);
		temp = "\n";
	    Write(temp, 100, ConsoleOutput);
    }
    else Exit(1);

    // failure case
    numWritten = Read(readBuffer, 22, outfile0);
    if(numWritten < 0){
	// printf("Read(): Failed: returned %d\n", numWritten);
	temp = "Read(): Failed: returned ";
	Write(temp, 100, ConsoleOutput);
    length = tostring(&num2stringBuffer, -numWritten);
    Write("-", 1, ConsoleOutput);
    Write(&num2stringBuffer, length+1, ConsoleOutput);
    temp = "\n";
	    Write(temp, 100, ConsoleOutput);
    }
    else Exit(1);

    rc = Close(outfile0);
    if(rc < 0){
	// printf("Close(): Failed: returned %d\n", rc);
	temp = "Close(): Failed: returned ";
	    Write(temp, 100, ConsoleOutput);
    length = tostring(&num2stringBuffer, -rc);
    // num2stringBuffer[0] = '-';
    Write("-", 1, ConsoleOutput);
    Write(&num2stringBuffer, length+1, ConsoleOutput);
		temp = "\n";
	    Write(temp, 100, ConsoleOutput);
    }
    else Exit(1);

  Exit(0);
}


