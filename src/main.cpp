#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/wait.h>
#include <boost/tokenizer.hpp>
#include "master_class.h"
#include "command.h"
#include "connectors.h"

using namespace std;

void make_tokens (string input, vector<string> &commands);
void parse (const vector <string> &input, vector<Rshell*> &treed_commands);

int main()
{
    bool exit_now = 0;
    string input;
    int status = 0;
    
    while(!exit_now)
    {
        cout << "$ ";
        
        getline(cin, input);
        vector<string> commands;
        vector<Rshell*> exe_commands;
        
        make_tokens(input, commands);
        parse(commands,exe_commands);
        
        exe_commands.at(exe_commands.size() - 1) -> execute(status, exit_now);
        status = 0;
        
        delete exe_commands.at(exe_commands.size() - 1);

        exe_commands.clear();
    }
}

void make_tokens (string input, vector<string> &commands)
{
        typedef boost::tokenizer<boost::char_separator<char> >     //this is taken from boost docs
        tokenizer;
        
        boost::char_separator<char> sep(" ", ";#");
        tokenizer tokens (input, sep);
        
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
        {   
            if(*tok_iter == "#")
            {
                break;
            }
                
            commands.push_back(*tok_iter);
        }
        
        return;
}

void parse (const vector <string> &input, vector<Rshell*> &treed_commands)
{
    // think about replacing Command* vector and instead use Rshell* vector and adjust from there.
    
    
    vector <string> connectors;
    vector <string> temp_vector;
    string temp;
    unsigned i = 0;
    
    while(i < input.size())                                  //takes all of the stings and makes them in to Command objects
    {                                                        // takes all the connectors and puts them into a vector of strings to be converted into a tree later
        temp = input.at(i);
        
        if(temp == "&&")                                     //checks for a && so it can start a new vector 
        {
            connectors.push_back(temp);
            Command* new_command = new Command(temp_vector);
            treed_commands.push_back(new_command);
            temp_vector.clear();   
        }
        else if(temp == "||")                                //checks for a || so it can start a new vector
        {
            connectors.push_back(temp);
            Command* new_command = new Command(temp_vector);
            treed_commands.push_back(new_command);
            temp_vector.clear();
        }
        else if (temp == ";")                                //checks for a ; so it can start a new vector
        {
            connectors.push_back(temp);
            Command* new_command = new Command(temp_vector);
            treed_commands.push_back(new_command);
            temp_vector.clear();
        }
        else
        {
            temp_vector.push_back(temp);
        }
        
        i++;
        
        if(i == input.size())
        {
            Command* new_command = new Command(temp_vector);
            treed_commands.push_back(new_command);
            temp_vector.clear();
        }
    }
    
    //------------------------------------------------
    // this is when we make the objects into a tree?
    //------------------------------------------------
    
    // special case for first one
    
    if(connectors.size() == 0)
    {
        return;
    }
    
    if(connectors.at(0) == "&&")
    {
        And* new_and = new And(treed_commands.at(0), treed_commands.at(1));
        treed_commands.erase(treed_commands.begin());
        treed_commands.erase(treed_commands.begin());
        connectors.erase(connectors.begin());
        treed_commands.push_back(new_and);
    }
    else if(connectors.at(0) == "||")
    {
        Or* new_or = new Or(treed_commands.at(0), treed_commands.at(1));
        treed_commands.erase(treed_commands.begin());
        treed_commands.erase(treed_commands.begin());
        connectors.erase(connectors.begin());
        treed_commands.push_back(new_or);
    }
    else if(connectors.at(0) == ";")
    {
        Semicolon* new_semi = new Semicolon(treed_commands.at(0), treed_commands.at(1));
        treed_commands.erase(treed_commands.begin());
        treed_commands.erase(treed_commands.begin());
        connectors.erase(connectors.begin());
        treed_commands.push_back(new_semi);
    }
    
    
    while(!connectors.empty())
    {
        int j = treed_commands.size() - 1;
        
        if(connectors.at(0) == "&&")
        {
            And* new_and = new And(treed_commands.at(j), treed_commands.at(0));
            treed_commands.push_back(new_and);
        }
        else if(connectors.at(0) == "||")
        {
            Or* new_or = new Or(treed_commands.at(j), treed_commands.at(0));
            treed_commands.push_back(new_or);
        }
        else if(connectors.at(0) == ";")
        {
            Semicolon* new_semi = new Semicolon(treed_commands.at(j), treed_commands.at(0));
            treed_commands.push_back(new_semi);
        }
        
        treed_commands.erase(treed_commands.begin());
        connectors.erase(connectors.begin());
    }

}
