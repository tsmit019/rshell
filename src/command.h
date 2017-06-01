#ifndef __COM_H__
#define __COM_H__

#include <iostream>
#include <vector>
#include <string>
#include "master_class.h"

using namespace std;

class Command : public Rshell
{
    private:
        vector <string> cmds_n_args;        //holds the command and the arguments of for execvp
        void test();                        //executes the "test" command
    
    public:
        Command(vector<string> commands) : cmds_n_args(commands) {};
        ~Command() {};
        void string_to_charptr(const vector <string> &commands, vector <char*> &char_cmds);
        void execute(int &status, bool &exit_now);
        string get_command() {return cmds_n_args.at(0); };
};

#endif
