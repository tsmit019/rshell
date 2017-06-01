#include <iostream>
#include "connectors.h"
#include "command.h"

using namespace std;

//----------------------------------------
// AND CLASS
//----------------------------------------

void And::execute(int &status, bool &exit_now)
{
    child_1 -> execute(status, exit_now);
    if(status == 0)
    {
        child_2 -> execute(status, exit_now);
    }
}

And::~And() {}

//----------------------------------------
// OR CLASS
//----------------------------------------

void Or::execute(int &status, bool &exit_now)
{
    child_1 -> execute(status, exit_now);
    
    if(status == -1)
    {
        child_2 -> execute(status, exit_now);
    }
}

Or::~Or() {}

//----------------------------------------
// SEMICOLON CLASS
//----------------------------------------

void Semicolon::execute(int &status, bool &exit_now)
{
    child_1 -> execute(status, exit_now);
    
    child_2 -> execute(status, exit_now);
}

Semicolon::~Semicolon() {}
