#ifndef __MASTER_H__
#define __MASTER_H__

#include <vector>
#include <iostream>
using namespace std;

class Master
{
    public:
        Master(vector<char*> commands) : cmds_n_args(commands) {}; 
        virtual void execute(int &status) = 0;
    protected:
        vector <char*> cmds_n_args;
};

#endif
