#include "foreground.h"

using namespace std;


void foreground(char *stringList[], char *oFile)
{
	//Create process and print error if unsuccesful
	pid_t pid = fork();
	if (pid < 0) {
		cerr << "Couldn't create process\n";
		exit(1);
	}
	
	//If process was succesful
	if (pid==0) { 


		//If there is a value in the output file, then send output to file
		if(oFile != NULL){
			int fd = open(oFile, O_WRONLY|O_CREAT, 0666);
			dup2(fd, 1);
			close(fd);
		}

		//change image of process
		execvp(stringList[0], stringList);
		cout << "Exec error!\n";
		exit(1);
	}

	//Wait for process to finish
	waitpid(pid, NULL, 0);
}