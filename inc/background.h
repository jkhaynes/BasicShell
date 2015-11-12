#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

//SYSTEM INCLUDES
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
A foreground job should be executed as follows:
1. Create a new process using fork
2. Replace the image of the created process with the desired command using execlp or
execvp.
3. Wait for the process to terminate using waitpid. 
**/

struct backJobs {
  char *argv[256];
  int pid;
};

backJobs* background(char *stringList[], char *oFile);

#endif //__BACKGROUND_H__