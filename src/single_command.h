#include "master_class.h"

class Single : public Master
{
    public:
        Single (vector<char*> commands) : cmds_n_args(commands) {};
        void execute(int &status);
        
    private:
         vector <char*> cmds_n_args;    //list of commands and arguments
};
