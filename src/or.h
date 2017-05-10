#ifndef __OR_H__
#define __OR_H__

#include "connector.h"
#include "master_class.h"

class Or : public Connector
{
    public:
        Or(vector<char*> left, vector<char*> right) : Connector(left, right) {};
        void execute(int &status);
};

#endif
