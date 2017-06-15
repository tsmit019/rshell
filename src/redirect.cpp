#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <stdio.h>

#include "redirect.h"

//----------------------------------------
// ABSTRACT REDIRECT CLASS
//----------------------------------------
Redirect::Redirect(Rshell* new_command, string new_filename)
{
    command = new_command;
    filename = new_filename;
}


//----------------------------------------
// INPUT REDIRECT CLASS
//----------------------------------------

Input_redirect::Input_redirect(Rshell* new_command, string new_filename) : Redirect(NULL, new_filename) {}

void Input_redirect::set_string_command(string new_scommand)
{
    string_command = new_scommand;
}

void Input_redirect::execute(int& status, bool& exit_now) 
{
    
    contents.push_back(string_command);
    contents.push_back(filename);
    
    Command* temp_command = new Command(contents);
    temp_command -> execute(status, exit_now);
    
    delete temp_command;
    
}

//----------------------------------------
// OUTPUT REDIRECT APPEND CLASS
//----------------------------------------

Output_append::Output_append(Rshell* new_command, string new_filename) : Redirect(new_command, new_filename) {}

void Output_append::execute(int &status, bool &exit_now)
{
    const int OUTPUT_FD = 1;
    
    FILE* output_file;
    output_file = fopen(filename.c_str(), "a");
    
    if (output_file != NULL)
    {
        int output_fd = fileno(output_file);
        int save_stdout = dup(1);
        close(1);
        
        dup(output_fd);
        command->execute(status, exit_now);
        
       close(output_fd);
       dup2(save_stdout, OUTPUT_FD);
    }

}


//----------------------------------------
// OUTPUT REDIRECT OVERWRITE CLASS
//----------------------------------------

Output_overwrite::Output_overwrite(Rshell* new_command, string new_filename) : Redirect(new_command, new_filename) {}

void Output_overwrite::execute(int &status, bool &exit_now)
{
    const int OUTPUT_FD = 1;
    
    FILE* output_file;
    output_file = fopen(filename.c_str(), "w");
    //cout << "Entered." << endl;
    if (output_file != NULL)
    {
        int output_fd = fileno(output_file);
        int save_stdout = dup(1);
        close(1);
        
        dup(output_fd);
        command->execute(status, exit_now);
        
        close(output_fd);
        dup2(save_stdout, OUTPUT_FD);
    }
    //cout << "Exit overwrite." << endl;
}
