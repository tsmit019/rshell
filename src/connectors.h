#ifndef __CONNECT_H__
#define __CONNECT_H__

#include "master_class.h"

//----------------------------------------
// ABSTRACT DELIMITER CLASS
//----------------------------------------

class Connector : public Rshell
{
    protected:
        Rshell *child_1;
        Rshell *child_2;
        
    public:
        Connector(Rshell *l_child, Rshell *r_child) : child_1(l_child), child_2(r_child) {};
        ~Connector() 
        {
            delete child_1;
            delete child_2;
        };
        virtual void execute(int &status, bool &exit_now) = 0;
};


//----------------------------------------
// AND CLASS
//----------------------------------------

class And : public Connector
{
    public:
        And(Rshell *l_child, Rshell *r_child) : Connector(l_child, r_child) {};
        ~And();
        void execute(int &status, bool &exit_now);
};

//----------------------------------------
// OR CLASS
//----------------------------------------

class Or : public Connector
{
    public:
        Or(Rshell *l_child, Rshell *r_child) : Connector(l_child, r_child) {};
        ~Or();
        void execute(int &status, bool &exit_now);
};

//----------------------------------------
// SEMICOLON CLASS
//----------------------------------------

class Semicolon : public Connector
{
    public:
        Semicolon(Rshell *l_child, Rshell *r_child) : Connector(l_child, r_child) {};
        ~Semicolon();
        void execute(int &status, bool &exit_now);
};

#endif
