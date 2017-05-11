#ifndef __MASTER_H__
#define __MASTER_H__

#include <vector>
#include <iostream>
using namespace std;

class Master
{
    public:
        Master() {}; 
        virtual ~Master() {};
        virtual void execute(int &status) = 0;
    protected:
};

#endif
