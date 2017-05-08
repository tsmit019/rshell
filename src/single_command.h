#include "master_class.h"

class Single : public Master
{
    public:
        Single (vector<char*> commands) : Master(commands) {};
        void execute(int &status);
        
    private:
};
