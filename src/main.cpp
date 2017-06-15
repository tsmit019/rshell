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
#include "redirect.h"

using namespace std;

void make_tokens (string input, vector<string> &commands);
void parse (const vector <string> &input, vector<Rshell*> &treed_commands);
bool even_parentheses(const vector <string> input_tokens);

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
        
        if(!even_parentheses(commands))                         //if there is an uneven number of parentheses
        {                                                       //throw an error and try again
            cout << "Error: uneven number of opening and closing parentheses" << endl;
        }
        else                                                    //if even or no parentheses execute the command(s)
        {
            parse(commands,exe_commands);
            // cout << "Size: " << exe_commands.size() - 1 << endl;
            //cout << "exe_commands size: " << exe_commands.size() << endl;
            exe_commands.at(exe_commands.size() - 1)->execute(status, exit_now);
            
            status = 0;
            
            
            delete exe_commands.at(exe_commands.size() - 1);
            exe_commands.clear();
        }
    }
}

void make_tokens (string input, vector<string> &commands)
{
        typedef boost::tokenizer<boost::char_separator<char> >     //this is taken from boost docs
        tokenizer;
        
        boost::char_separator<char> sep(" ", ";#()");
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
    vector <Rshell*> temp_objects;
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
            temp_objects.push_back(new_command);
            temp_vector.clear();   
        }
        else if(temp == "||")                                //checks for a || so it can start a new vector
        {
            connectors.push_back(temp);
            Command* new_command = new Command(temp_vector);
            temp_objects.push_back(new_command);
            temp_vector.clear();
        }
        else if(temp == ";")                                //checks for a ; so it can start a new vector
        {
            connectors.push_back(temp);
            Command* new_command = new Command(temp_vector);
            temp_objects.push_back(new_command);
            temp_vector.clear();
        }
        else if(temp == ">")
        {
            Rshell* new_command;
            if(temp_vector.empty())
            {
                new_command = treed_commands.at( treed_commands.size() - 1);
            }
            else
            {
                new_command = new Command(temp_vector);
            }
            
            i++;
            string temp_filename = input.at(i);
        
            Redirect* new_redirect = new Output_overwrite(new_command, temp_filename);
            temp_objects.push_back(new_redirect);
            temp_vector.clear();
            
            //cout << "here 1" << endl;
        }
        else if(temp == ">>")
        {
            //cout << "Finding something" << endl;
            Command* new_command = new Command(temp_vector);
            i++;
            string temp_filename = input.at(i);
            //cout << temp_filename << endl;
            Redirect* new_redirect = new Output_append(new_command, temp_filename);
            temp_objects.push_back(new_redirect);
            temp_vector.clear();
            
            //cout << "here 1" << endl;
        }
        else if(temp == "<")
        {
            string temp_command = input.at(i - 1);
            i++;
            string temp_filename = input.at(i);
            Input_redirect* new_redirect = new Input_redirect(NULL, temp_filename);
            new_redirect -> set_string_command(temp_command);
            temp_objects.push_back(new_redirect);
            temp_vector.clear();
        }
        else if(temp == "(")
        {
            int par_count = 1;
            unsigned q = i;
            q++;
            vector <string> temp_vec;
            
            while(par_count != 0)
            {
                if(input.at(q) == "(")
                {
                    temp_vec.push_back(input.at(q));
                    par_count++;
                }
                else if(input.at(q) == ")")
                {
                    par_count--;
                    if(par_count != 0)
                    {
                        temp_vec.push_back(input.at(q));
                    }
                }
                else
                {
                    temp_vec.push_back(input.at(q));
                }
                
                q++;
            }
            parse(temp_vec, treed_commands);
            //cout << q << endl;
            if(q < input.size() && (input.at(q) == "&&" || input.at(q) == "||" || input.at(q) == ";"))
            {
                connectors.push_back(input.at(q)); 
            }
            i = q;
        }
        else
        {
            //cout << "pushed on" << endl;
            temp_vector.push_back(temp);
        }
        
        i++;
        
        if(i == input.size())
        {
            //cout << "new object" << endl;
            Command* new_command = new Command(temp_vector);
            temp_objects.push_back(new_command);
            temp_vector.clear();
        }
    }
    
    //------------------------------------------------
    // this is when we make the objects into a tree?
    //------------------------------------------------
    
    if(connectors.size() == 0)                        // if there is no connectors then there is only one Rshell object
    {                                                 // execute that sucker
        if(temp_objects.size() != 0)
        {
            treed_commands.push_back(temp_objects.at(temp_objects.size() - 1));
        }
        return;
    }
    
    if(temp_objects.size() == 0)
    {
        for(unsigned r = 0; r < treed_commands.size(); r++)
        {
            temp_objects.push_back(treed_commands.at(r));
        }
    }
    // special case for first connector, because it should get the 1st two Rshell objects
    // the following should get the first Rshell object and the last
    
    //cout << connectors.size() << endl;
    
    if(connectors.at(0) == "&&")
    {
        And* new_and = new And(temp_objects.at(0), temp_objects.at(1));
        temp_objects.erase(temp_objects.begin());
        temp_objects.erase(temp_objects.begin());
        connectors.erase(connectors.begin());
        temp_objects.push_back(new_and);
    }
    else if(connectors.at(0) == "||")
    {
        Or* new_or = new Or(temp_objects.at(0), temp_objects.at(1));
        temp_objects.erase(temp_objects.begin());
        temp_objects.erase(temp_objects.begin());
        connectors.erase(connectors.begin());
        temp_objects.push_back(new_or);
    }
    else if(connectors.at(0) == ";")
    {
        Semicolon* new_semi = new Semicolon(temp_objects.at(0), temp_objects.at(1));
        temp_objects.erase(temp_objects.begin());
        temp_objects.erase(temp_objects.begin());
        connectors.erase(connectors.begin());
        temp_objects.push_back(new_semi);
    }
    
    while(!connectors.empty())                                         //makes commands out of the connectors and the
    {                                                                  //Rshell objects specifically first and last
        int j = temp_objects.size() - 1;
        
        if(connectors.at(0) == "&&")
        {
            And* new_and = new And(temp_objects.at(j), temp_objects.at(0));
            temp_objects.push_back(new_and);
        }
        else if(connectors.at(0) == "||")
        {
            Or* new_or = new Or(temp_objects.at(j), temp_objects.at(0));
            temp_objects.push_back(new_or);
        }
        else if(connectors.at(0) == ";")
        {
            Semicolon* new_semi = new Semicolon(temp_objects.at(j), temp_objects.at(0));
            temp_objects.push_back(new_semi);
        }
        
        temp_objects.erase(temp_objects.begin());
        connectors.erase(connectors.begin());
    }
    
    treed_commands.push_back(temp_objects.at(temp_objects.size() - 1)); //adding your final product back onto the tree
}

bool even_parentheses(const vector <string> input_tokens)
{
    //this function essentially just checks is there is an even number of parantheses
    //thats is
    int left_paren = 0, right_paren = 0;
    
    for(unsigned i = 0; i < input_tokens.size(); i++)
    {
        if(input_tokens.at(i) == "(")
        {
            left_paren++;
        }
        else if(input_tokens.at(i) == ")")
        {
            right_paren++;
        }
    }
    
    if(left_paren == right_paren)
    {
        return true;
    }
    
    return false;
}
