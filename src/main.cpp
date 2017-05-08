#include <iostream>
#include <cstdio>
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
#include "single_command.h"

//ls -a; echo hello && mkdir test || echo world; git status

void make_tokens(string input, vector<string> &commands);
void string_to_charpt(const vector <string> &commands, vector <char*> &char_cmds);

using namespace std;
int main() {

    string input;
    
    while (1) 
    {
        cout << "$ ";
        getline(cin, input);

        vector<string> cmds;
        make_tokens(input, cmds);
        vector<char*> char_cmds;
        
        if ( cmds.at(0) == "exit" )                //checks if first command is exit then exits
        {
            break;
        }
        
        string_to_charpt(cmds, char_cmds);        //this converts vector<string> to vector<char*>
        
        // for(int q = 0; q < char_cmds.size(); q++)
        // {
        //     cout << char_cmds.at(q) << endl;
        // }
        
        int stat = 0;
        Single *testies = new Single(char_cmds);
        testies -> execute(stat);
        
        //remember to delete the vector<char*>
        for(unsigned x = 0; x < char_cmds.size(); x++)
        {
            delete [] char_cmds[x];
        }
    }
    
    return 0;
}

void make_tokens(string input, vector<string> &commands)
{
        typedef boost::tokenizer<boost::char_separator<char> >     //this is taken from boost docs
        tokenizer;
        
        boost::char_separator<char> sep(" ", ";#");
        tokenizer tokens (input, sep);
        
        for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
        {   
            commands.push_back(*tok_iter);
        }
        
        return;
}

void string_to_charpt(const vector <string> &commands, vector <char*> &char_cmds)
{
    
    for(unsigned i = 0; i < commands.size(); i++)
    {
        string temp = commands.at(i);
        char *cstr = new char[temp.length() + 1];
        strcpy(cstr, temp.c_str());
        
        char_cmds.push_back(cstr);
    }
    
    char_cmds.push_back(NULL);
        
    return;
}
