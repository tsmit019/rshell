#ifndef __PIPE_H__
#define __PIPE_H__

#include <string>
#include <vector>
#include "master_class.h"

using namespace std;

class Pipe : public Rshell
{
    private:
        vector <string> list_o_pipes;
        
    public:
        Pipe(vector <string> pipes);
        ~Pipe () {};
        void string_to_charptr(const vector <string> &commands, vector <char*> &char_cmds);
        void execute(int &status, bool &exit_now);
    
};

#endif

