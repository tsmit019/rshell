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
#include "single_command.h"
#include "connector.h"
#include "and.h"
#include "or.h"

//ls -a; echo hello && mkdir test || echo world; git status

void make_tokens(string input, vector<string> &commands);

void string_to_charpt(const vector <string> &commands, vector <char*> &char_cmds);

void parse(const vector <char*> &char_commands, 
    vector <vector <char*> > &command_list, vector <char*> &connectors);    //parses into seperate commands
    
void execute_order_66(vector <vector <char*> > &command_list,
    vector <char*> &connectors, bool &yo_we_exit, int &status, unsigned &x);               //executes the commands

using namespace std;
int main() {

    string input;
    int status;
    bool dont_exit = 1;
    
    while (dont_exit) 
    {
        cout << "$ ";
        getline(cin, input);

        vector<string> cmds;
        make_tokens(input, cmds);
        vector<char*> char_cmds;
        string_to_charpt(cmds, char_cmds);              //this converts vector<string> to vector<char*>
        
        vector <vector <char*> > command_list;
        vector <char*> connectors;
        unsigned x = 0;
         
        parse(char_cmds, command_list, connectors);    //this parses the input so multiple 
                                                        //commands can be executed
        execute_order_66(command_list, connectors, dont_exit, status, x);
        
        for (unsigned x = 0; x < char_cmds.size(); x++)
        {
            delete [] char_cmds[x];
            
        }
        
        // for (unsigned q = 0; q < connectors.size(); q++)
        // {
        //     delete [] connectors[q];
            
        // }
        
        // for(unsigned r = 0; r < command_list.size(); r++)
        // {
        //     for(unsigned s = 0; s < command_list.at(r).size(); s++)
        //     {
        //         delete [] command_list.at(r)[s];
        //     }
        // }
        
        if(!dont_exit)
        {
            break;
        }
    }
    
    return 0;
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

void string_to_charpt(const vector <string> &commands, vector <char*> &char_cmds)
{
    
    for (unsigned i = 0; i < commands.size(); i++)
    {
        string temp = commands.at(i);
        char *cstr = new char[temp.length() + 1];
        strcpy(cstr, temp.c_str());
        
        char_cmds.push_back(cstr);
    }
    
    char_cmds.push_back(NULL);
        
    return;
}

void parse (const vector <char*> &char_commands, 
    vector <vector <char*> > &command_list, vector <char*> &connectors)
{
    int i = 0;
    vector <char*> temp_vector;
    
    while (char_commands.at(i) != NULL)
    {
        char* temp = char_commands.at(i);
        
        if (strcmp(temp, "&&") == 0 )        //checks for a && so it can start a new vector 
        {
            //cout << "you we got a fresh &&" << endl;
            temp_vector.push_back(NULL);
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
        else if (strcmp(temp, "||") == 0 )    //checks for a || so it can start a new vector
        {
            //cout << "you we got a fresh ||" << endl;
            temp_vector.push_back(NULL);
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
        else if (strcmp(temp, ";") == 0 )     //checks for a ; so it can start a new vector
        {
            //cout << "you we got a fresh ;" << endl;
            temp_vector.push_back(NULL);
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
            //cout << char_commands.at(i) << endl;
            temp_vector.push_back( char_commands.at(i) );
        
        i++;
    }
    
    temp_vector.push_back(NULL);
    command_list.push_back(temp_vector);
    
}

void execute_order_66(vector <vector <char*> > &command_list, vector <char*> &connectors, 
    bool &yo_we_exit, int &status, unsigned &x)
{
    int connectorsCount = connectors.size();
    if(status == -1)
    {
        yo_we_exit = 0;
        return;
    }
    
    if(connectors.size() == 0)
    {
        //cout << command_list.at(0).at(0) << endl;
        
        
        if(strcmp(command_list.at(0).at(0), "exit") == 0) {
            yo_we_exit = 0;
            return;
        }
        
        Single *single_it_out = new Single(command_list.at(0));
        single_it_out->execute(status);
        
        delete single_it_out;
    }
    
   // int x = 0;
    bool lastRun = false;
    int start = 0;
    for(unsigned i = 0; i < connectors.size(); i++)
    {
      if (x > command_list.size()) {
          yo_we_exit = 0;
          return;
      }
        if (status == -1)
        {
            yo_we_exit = 0;
            return;
        }
        
        char* current_connector = connectors.at(i);
        
        if(strcmp(current_connector, "&&") == 0)
        {
            if (lastRun == true || start == 0) 
            {
                if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                {
                   yo_we_exit = 0;
                  return;
                }
                
            Single *cmd1 = new Single(command_list.at(x));
            cmd1->execute(status);
            delete cmd1;
            start++;
            if (status != -1) 
            {
                lastRun = true;
                x++;
                
                if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                {
                    yo_we_exit = 0;
                    return;
                }
                Single *cmd2 = new Single(command_list.at(x));
                cmd2->execute(status);
                delete cmd2;
                x++;
            }
            else 
            {
                lastRun = false;
            }
            }
            connectorsCount--;
        }
        else if(strcmp(current_connector, "||") == 0)
        {
            if (lastRun == false || start == 0) 
            {
                lastRun = true;
                start++;
                
                if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                {
                yo_we_exit = 0;
                return;
                }
                
                  Single *cmd1 = new Single (command_list.at(x));
                  cmd1->execute(status);
                  delete cmd1;
                  if (status == -1) 
                  {
                      x++;
                    if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                    {
                   yo_we_exit = 0;
                return;
                   } 
            
             Single *cmd2 = new Single(command_list.at(x));
             cmd2->execute(status);
             x++;
             delete cmd2;
                  }
        
            else
            {
                lastRun = false;
            }
        
            }
            connectorsCount--;
        }
        else if(strcmp(current_connector, ";") == 0)
        {
            cout << "Found semicolon:" << endl;
            connectorsCount--;
            cout << "Connectors remaining: " << connectorsCount << endl;
           lastRun = false;
           start = 0;
           if (connectorsCount == 0) {
            Single *single_it_out = new Single(command_list.at(x));
            single_it_out->execute(status);
           }
            
            
        }
        
    }
         
    
}
