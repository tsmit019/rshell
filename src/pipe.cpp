#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>

#include "command.h"
#include "pipe.h"
using namespace std;

Pipe::Pipe(vector <string> pipes)
{
    list_o_pipes = pipes;
}

void Pipe::execute(int &status, bool &exit_now)
{
    cout << "doesnt quite work" << endl;
    
    for(unsigned q = 0; q < list_o_pipes.size(); q++)
    {
        cout << list_o_pipes.at(q) << endl;
    }
    return;
    
    const int READ_FD = 0;
    const int WRITE_FD = 1;
    unsigned i = 0;
    int fd[2];
    int save_stdin = dup(0);
    int save_stdout = dup(1);
    vector <string> temp_vector;
    
    pipe(fd);
    
    while(i < list_o_pipes.size())
    {
        string temp = list_o_pipes.at(i);
        
        if(temp == "|")
        {
            //then we will execute the command with pipe
            
            int status_pid = 0;
            // change the strings to char* here and then execute from there
            // this way all we have to do is deal with strings and that is no much easier
            
            vector <char*> char_cmds;
            string_to_charptr(temp_vector, char_cmds);
            
            char** command = &char_cmds[0];
            
            int pid;
            pid = fork();
            
            if(pid == 0)
            {
                dup2(fd[1],WRITE_FD);
                execvp(command[0], command);
                perror("Error: execvp");
                exit(1);
        
            }
            else if (pid > 0)
            {
                
                waitpid(pid, &status_pid, 0);
            }
            else
            {
                perror("Error");
                return;
                //cout << WIFEXITED(status_pid) << endl;
                //perror("Error");  this is ways return "sucess" 
            }
            
            if(WIFEXITED(status_pid))                            //if the child process exited correctly
            {
                //checks to see if anything fucked up during the child process
                //if it did we make sure that info is known
                
                int child_run_stat = 0;
                
                child_run_stat = WEXITSTATUS(status_pid);        //checks the exit status of the child process
                
                if (child_run_stat == 1)                         //if execvp failed the set status to -1 
                {
                    status = -1;
                }
               
            }
            
            for (unsigned x = 0; x < char_cmds.size(); x++)       //makes sure all of that dank heap mem got dealocated
            {
                delete [] char_cmds[x];
            }
            
        }
        else
        {
            temp_vector.push_back(temp);
        }
        i++;
    }
}

void Pipe::string_to_charptr(const vector <string> &commands, vector <char*> &char_cmds)
{
    //change strings to char*
    for (unsigned i = 0; i < commands.size(); i++)
    {
        string temp = commands.at(i);
        char *cstr = new char[temp.length() + 1];             //allocates new memory so we can have of char*
        strcpy(cstr, temp.c_str());                           //makes a copy as a c_string
        
        char_cmds.push_back(cstr);
    }
    
    char_cmds.push_back(NULL);                                //makes sure the c_string is null terminated
        
    return;
}
