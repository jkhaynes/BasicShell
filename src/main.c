#include "foreground.h"
#include "background.h"
#include "piped.h"

//SYSTEM INCLUDES
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{

    int totalBJ = 0;
    backJobs *back[100];
    while(true){

        cout << "wsh: ";
	    std::string a[256];
        int i=0;
        char *oFile = NULL;
        bool isBJ = false;
        bool isPiped= false;
        int n = 0;
        backJobs toAdd;
        bool fileOpened = true;

        //Read in input one word at a time and store in string a[]

        do{
            cin>>a[i++];
        } while(cin.peek() != '\n');

        char *stringList[256];

        int j = 0;
        int k = 0;
        int l = 0;

        //move from string a into char *stringList[], the appropriate type for execvp

        char *command = const_cast<char*>(a[0].c_str());

        for(j= 0 ; j < i ; j++){

    	    char *check = const_cast<char*>(a[j].c_str());

            //if first word typed is exit, then exit program

            if(strcmp (command, "exit") == 0){
                stringList[0] = command;
                break;
            }

            else if(strcmp (command, "wait") == 0){
                j++;
                stringList[0] = command;
                int toWait = atoi(a[j].c_str()) -1;

                if(toWait < totalBJ){
                    int pid = back[toWait]->pid;
                    waitpid(pid, NULL, 0);
                }

                else{
                    cout << "Number not associated with background process.\n";
                }
            }

            //if first word typed is cd, then change directory

            else if(strcmp (command, "cd") == 0){
                stringList[0] = command;

                if(i < 2){
                    cout << "null";
                }
                else{
                    char *dir = const_cast<char*>(a[1].c_str());

                    int rc = chdir(dir);
                    if (rc < 0) {
                        cout << "Directory does not exist\n";
                    }

                    else{
                        int MAXPATHLEN = 256;
                        char buffer[MAXPATHLEN];
                        char *path = getcwd(buffer, MAXPATHLEN);
                        cout << "Working directory ";
                        for (int i = 0; i < strlen(path); i++){
                            cout << path[i];
                        }
                        cout << "\n";
                    }

                }
                break;
            }

            //if a[i] is > then set name of output file

    	    else if(strcmp (check, ">") == 0){
    		    j++;
    		    oFile = const_cast<char*>(a[j].c_str());
    	    } 

            //if a[i] is < then read in from given file and add to stringList[]

    	    else if(strcmp (check, "<") == 0){
    		    std::string STRING;
			    ifstream infile;
			     j++;
			     infile.open (const_cast<char*>(a[j].c_str()));
			     std::string word;

                if(infile.is_open()){

       	            while (infile >> word){
   				         stringList[l] = const_cast<char*>(word.c_str());
   				         l++;
			        }

		            infile.close();

                }

                else{
                    fileOpened = false;
                    break;
                }

    	    }

            //if a[i] is &, then mark as background

            else if(strcmp (check, "&") == 0){
                isBJ = true;
            }

            //else add any other characters to stringList[]

            else{

                //if char is | then mark as pipe

                if(strcmp(check, "|") == 0){
                    isPiped = true;
                    n+=1;
                }

        	    stringList[l] =  check;
        	    k++;
        	    l++;
            }
        }

        //if exit command, leave program

        if(fileOpened == false){
            cout << "File does not exist.\n";
        }

        else if(strcmp (stringList[0], "exit") == 0){
            break;
        }

        else if(strcmp (stringList[0], "wait") == 0){
        }

        //if cd command, do nothing as already handled

        else if(strcmp (stringList[0], "cd") == 0){
        }

        //if piped, send to piped()

        else if(isPiped == true){
            n += 1;
            stringList[l] = NULL;
            piped(stringList, n);
        }

        //if background, then send to background()

        else if(isBJ == true){
            stringList[l] = NULL;
            backJobs *toAdd = background(stringList, oFile);
            back[totalBJ] = toAdd;
            totalBJ++;
        }

        //else send to foreground()

        else{

            stringList[l] = NULL;
            foreground(stringList, oFile);
        }

        if(totalBJ > 0){

            int ct;

            cout << "    Running:";

            for(ct = 0; ct < totalBJ; ct++){

                cout << "\n        " << "[" << ct+1 << "] " ;

                int count = 0;
                while(true){
                    cout << back[ct]->argv[count] << " ";
                    count++;
                
                    if(back[ct]->argv[count] == NULL){    
                        break;
                    }
                }
                
            }
             cout << "\n";
        } 
    }
    return 0;
}
