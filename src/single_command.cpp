#include "single_command.h"
#include "master_class.h"
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>

void Single::execute(int &status)
{
   
    char** command = &cmds_n_args[0];
    
    int pid;
    pid = fork();
    
    if(pid == -1)
    {
        perror("Error");
        return;
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        //perror("Error");  this is ways return "sucess" full is it is
    }
    else
    {
       status = execvp(command[0], command);
       perror("Error");
    }
}

