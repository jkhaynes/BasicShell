#ifndef __PIPED_H__
#define __PIPED_H__

//SYSTEM INCLUDES
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <cstdlib>
#include <cstdio>

#include <string.h>

/**
A foreground job should be executed as follows:
1. Create a new process using fork
2. Replace the image of the created process with the desired command using execlp or
execvp.
3. Wait for the process to terminate using waitpid. 
**/

void piped(char *stringList[], int n);

#endif //__PIPED_H__