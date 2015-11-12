#include "piped.h"

using namespace std;

void piped(char *stringList[], int n)
{
    int i;
    int j = 0; //used to increment through stringList
    pid_t pid;
    int input; //used to store value of where process should get input
    int fd [2];
    
    //initliaze first process to get input from standard input
    input = 0;

    //creates a new process for jobs 0 through n-1
    //creates n-1 pipes using pipe
    //redirects the input of job i to the write end of pipe i
    //redirects the output of job i to the read end of pip i-1
    //keeps the input of job 1 as standard input because of in being initialized to 0
    //changes the image of job 0 through n-1

    //DOES NOT handle or create process n or job n
    for (i = 0; i < n - 1; ++i){

        //creates a new char array to store the current commands to change image to
        char *curList[256];

        pipe (fd);

        char *check = stringList[j];

        int k = 0;

        while(true){

            curList[k] = check;
            j+=1;
            k+=1;

            check = stringList[j];

            //Checks to see if we've hit the end of stringList[] or a | character, if so then breaks

            if(check == NULL || strcmp(check, "|") == 0){
                break;
            }
        }

        j+=1;

        curList[k] = NULL;

        //curList now holds the new image for the current process

        //output process set to write end of pipe i
        int output = fd[1];

        pid_t pid;

        if ((pid = fork ()) == 0){

            //send input of process i to input, which is standard input for 
            //process 0 and the read end of pipe i-1 for all others
        
            if (input != 0){
                dup2 (input, 0);
                close (input);
            }

            //send output of process i to output, which is the write end of pipe i

            if (output != 1){
                dup2 (output, 1);
                close (output);
            }

            //change image for process i to curList

            execvp (curList[0], curList);
            cout << "Exec error!\n";
            exit(1);
        
        }

        close (fd [1]);

        //update input to read end of pipe i
        input = fd [0];
    }

    //handle last process

    char* curList[256];

    char *check = stringList[j];

    int k = 0;

    while(true){

        curList[k] = check;
        j+=1;
        k+=1;

        check = stringList[j];

        if(check == NULL || strcmp(check, "|") == 0){
            break;
        }
    }

    j+=1;

    curList[k] = NULL;

    //curList now contains the last set of commands

    //create process n
    if ((pid = fork ()) == 0){

        //send input of process i to input, which is
        //the read end of the last pipe 

        if (input != 0){
            dup2 (input, 0);
            close (input);
        }

        //no need to send output anywhere, as it stays going to standard output

        //change image of last process

        execvp (curList[0], curList);
        cout << "Exec error!\n";
        exit(1);
        
    }

    //wait for the last process to finish

    waitpid(pid, NULL, 0);

}
