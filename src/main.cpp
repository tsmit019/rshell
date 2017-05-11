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
    
    while (dont_exit) //will always print the '$' character.
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
         
        parse(char_cmds, command_list, connectors);     //this parses the input so multiple 
                                                        //commands can be executed
        execute_order_66(command_list, connectors, dont_exit, status, x); //commands are executed here.
        //command_list is the vector of commands in the input
        //connectors is the vector of connectors in the input
        //dont_exit is the trigger that will tell the program to leave.
        //int status is the status of the command which will determine if the command ran successfully.
        //x was initally used as a counter, currently serves no purpose as a parameter.
        
        for (unsigned x = 0; x < char_cmds.size(); x++)
        {
            delete [] char_cmds[x];
            
        }
        
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
//converts vector of string into a vector of character pointers.
{
    
    for (unsigned i = 0; i < commands.size(); i++)
    {
        string temp = commands.at(i);
        char *cstr = new char[temp.length() + 1];             //allocates new memory so we can have of char*
        strcpy(cstr, temp.c_str());                           //makes a copy as a c_string
        
        char_cmds.push_back(cstr);
    }
    
    char_cmds.push_back(NULL);                                //makes sure the c_string is null terminated
        
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
            temp_vector.push_back(NULL);     //makes sure the end of the c_string is null
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
        else if (strcmp(temp, "||") == 0 )    //checks for a || so it can start a new vector
        {
            temp_vector.push_back(NULL);      //makes sure the end of the c_string is null
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
        else if (strcmp(temp, ";") == 0 )     //checks for a ; so it can start a new vector
        {
            temp_vector.push_back(NULL);      //makes sure the end of the c_string is null
            command_list.push_back(temp_vector);
            temp_vector.clear();
            connectors.push_back(temp);
            i++;
        }
            temp_vector.push_back( char_commands.at(i) );
        
        i++;
    }
    
    temp_vector.push_back(NULL);              //when no delimiter is found still null terminates
    command_list.push_back(temp_vector);      //pushes the vector with the command onto the list of...
                                              //commands
    
}

void execute_order_66(vector <vector <char*> > &command_list, vector <char*> &connectors, 
    bool &yo_we_exit, int &status, unsigned &x)
{
    int connectorsCount = connectors.size();
    int commandCount = command_list.size();
    if(status == -1)
    {
        yo_we_exit = 0;
        return;
    }
    
    if(connectors.size() == 0) //checks if the input is a single command.
    {
        
        
        if(strcmp(command_list.at(0).at(0), "exit") == 0) {
            yo_we_exit = 0;
            return;
        }
        
        Single *single_it_out = new Single(command_list.at(0));
        single_it_out->execute(status);
        
        delete single_it_out;
    }
    
    bool lastRun = false; //Checks if the last program ran.
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
        
        if(strcmp(current_connector, "&&") == 0) //checks if the current connector being processed is AND.
        {
            if (lastRun == true || start == 0) 
            {
                if(strcmp(command_list.at(x).at(0), "exit") == 0) //exits if the command is 'exit'
                {
                   yo_we_exit = 0;
                  return;
                }
                
            Single *cmd1 = new Single(command_list.at(x));
            cmd1->execute(status);
            delete cmd1;
            start++;
            if (status != -1) //if the first command ran successfully, run the next one.
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
            commandCount--;
            commandCount--;
        }
        else if(strcmp(current_connector, "||") == 0)//checks if the current connector being processed is OR.
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
                x++;
                x++;
            }
        
            }
            connectorsCount--;
            commandCount--;
            commandCount--;
        }
        else if(strcmp(current_connector, ";") == 0) //checks if the current connector being processed is ';'.
        {
            if (command_list.size() == 2) { //checks if it is 2 consecutive commands.
            
                if(strcmp(command_list.at(0).at(0), "exit") == 0) 
                {
                    yo_we_exit = 0;
                    return;
                }
    
                Single *cmdfirst = new Single(command_list.at(0));
                cmdfirst->execute(status);
                delete cmdfirst;
               
                
                if(strcmp(command_list.at(1).at(0), "exit") == 0) 
                {
                    yo_we_exit = 0;
                    return;
                }
                
                Single *cmdsecond = new Single(command_list.at(1));
                cmdsecond->execute(status);
                delete cmdsecond;
                return;
            }
            connectorsCount--;
           lastRun = false;
           if (i != connectors.size()-1) { //nothing happens if there are more connectors to be processed unless..

               
                bool is_semi = 0;
                if(strcmp(connectors.at(i + 1), ";") == 0)
                {
                    is_semi = 1;
                }
                if (is_semi) { //if the next command is a 'single command' before a semicolon.
                   
                    if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                    {
                        yo_we_exit = 0;
                        return;
                    }
                    
                    Single *cmd3 = new Single(command_list.at(x)); //runs the single command.
                    cmd3->execute(status);
                    x++;
                    delete cmd3;
                    connectorsCount--;
                }
           }
           if (connectorsCount==0) { //if the input is a series of commands separated by semicolons.
             
               if(strcmp(command_list.at(x).at(0), "exit") == 0) 
                {
                    yo_we_exit = 0;
                    return;
                }
               
               Single *cmd4 = new Single(command_list.at(x));
               cmd4->execute(status);
               x++;
               delete cmd4;
           }
            
            
        }
        
    }
         
    
}

