#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include "command.h"

using namespace std;

void Command::execute(int &status, bool &exit_now)
{
    
    if(cmds_n_args.at(0) == "test" || cmds_n_args.at(0) == "[")
    {
        test();
        return;
    }
    
    if(cmds_n_args.at(0) == "exit")
    {
        exit_now = 1;
        return;
    }
    
    int status_pid = 0;
    // change the strings to char* here and then execute from there
    // this way all we have to do is deal with strings and that is no much easier
    
    vector <char*> char_cmds;
    string_to_charptr(cmds_n_args, char_cmds);
    
    char** command = &char_cmds[0];
    
    int pid;
    pid = fork();
    
    if(pid == 0)
    {
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

void Command::string_to_charptr(const vector <string> &commands, vector <char*> &char_cmds)
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

void Command::test()
{
    //check to see if the file path exits (i.e. .at(2) is a valid file path)
    
    string file_path;
    struct stat s;
    
    if(cmds_n_args.at(0) == "[")
    {
        file_path = cmds_n_args.at( cmds_n_args.size() - 2);
    }
    else if(cmds_n_args.at(0) == "test")
    {
        file_path = cmds_n_args.at( cmds_n_args.size() - 1);
    }
    
    if(cmds_n_args.at(1) == "-f")
    {
        if( stat(file_path.c_str(),&s) == 0 )
        {
            if( s.st_mode & S_IFREG )
            {
                //the filepath leads to a "regular" file
                cout << "(True)" << endl;
            }
            else
            {
                cout << "(False)" << endl;
            }
        }
        else
        {
            cout << "(False)" << endl;
        }
        
    }
    else if(cmds_n_args.at(1) == "-d")
    {
        if( stat(file_path.c_str(),&s) == 0 )
        {
            if(s.st_mode & S_IFDIR)
            {
                //the filepath leads to a "regular" file
                cout << "(True)" << endl;
            }
            else
            {
                cout << "(False)" << endl;
            }
        }
        else
        {
            cout << "(False)" << endl;
        }
    }
    else
    {
        if( stat(file_path.c_str(),&s) == 0 )
        {
            cout << "(True)" << endl;
        }
        else
        {
            cout << "(False)" << endl;
        }
    }
    
}
