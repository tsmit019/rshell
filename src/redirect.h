#ifndef __REDI_H__
#define __REDI_H__

#include <string>
#include "master_class.h"
#include "command.h"

//----------------------------------------
// ABSTRACT REDIRECT CLASS
//----------------------------------------
class Redirect: public Rshell
{
    protected:
        Rshell* command;
        string filename;
    public:
        Redirect (Rshell* new_command, string new_filename);
        ~Redirect() {delete command;};
        virtual void execute(int &status, bool &exit_now) = 0;
    
};

//----------------------------------------
// INPUT REDIRECT CLASS
//----------------------------------------
class Input_redirect: public Redirect
{
    private:
        vector<string> contents;
        string string_command;
        
    public:
        Input_redirect(Rshell* new_command, string new_filename);
        ~Input_redirect() {};
        void execute(int &status, bool &exit_now);
        void set_string_command(string new_command);
        //this class may need some more functions, and even some private ones
        //needs to take info from the file -> make the string into tokens -> put into a vector
        // -> make a Command object
};

//----------------------------------------
// OUTPUT REDIRECT APPEND CLASS
//----------------------------------------
class Output_append : public Redirect
{
    private:
    public:
        Output_append(Rshell* new_command, string filename);
        ~Output_append() {};
        void execute(int &status, bool &exit_now);
};

//----------------------------------------
// OUTPUT REDIRECT OVERWRITE CLASS
//----------------------------------------
class Output_overwrite : public Redirect
{
    private:
    public:
        Output_overwrite(Rshell* new_command, string filename);
        ~Output_overwrite() {};
        void execute(int &status, bool &exit_now);
};

#endif
