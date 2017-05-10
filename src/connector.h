#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <iostream>
#include <vector>
#include "master_class.h"

class Connector : public Master
{
    protected:
    vector<char*> left;
    vector<char*> right;
    //int status;
    
    public:
    Connector(vector<char*> left, vector<char*> right);
    virtual void execute(int &status) = 0;
};

#endif
