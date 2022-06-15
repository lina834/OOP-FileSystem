//CommandPrompt.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for the command line

#include "CommandPrompt.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream> 

using namespace std;
//constructor
CommandPrompt::CommandPrompt()
    :abFile(nullptr), abFileFac(nullptr){}

//set the file system
void CommandPrompt::setFileSystem(AbstractFileSystem* a)
{
    abFile = a;
}

//set the file factory
void CommandPrompt::setFileFactory(AbstractFileFactory* a)
{
    abFileFac = a;
}

//add a command to the list of available commands
//parameters:
//  s     the name of the command being added
//  ac    a pointer to the command being added
//return values:
//  0   success
//  2   addCommand_failed
int CommandPrompt::addCommand(string s, AbstractCommand* ac)
{ 
    if (abMap.insert(pair<string,AbstractCommand*>(s, ac)).second == false) 
    {
        //could not insert into the map
        return static_cast<int>(cpRet::addCommand_failed);
    } 
    return static_cast<int>(cpRet::success);
}

//run the command line
//no parameters
//return values:
//  0   success
//  1   quit
int CommandPrompt::run()
{
    while (1)
    {
        string p = prompt();
        if (p == "q")
        {
            //quit
            return static_cast<int>(cpRet::quit);
        }
        else if (p == "help")
        {
            //list all commands
            listCommands();
        }
        else if (abMap.find(p)!=abMap.end())
        {
            //found command, execute with empty string
            string emptyString = string();
            abMap.find(p)->second->execute(emptyString);
        }
        else
        {
            istringstream s(p); //separates by whitespace

            string first; //command word
            string rest; //rest of the line
            if (s >> first)
            {
                if (first == "help")
                {

                    if (getline(s,rest))
                    { 
                        //there is another phrase afterwards, get the entire phrase
                        rest = rest.substr(1, rest.length()); //get rid of the space in the beginning
                        if (abMap.find(rest) == abMap.end()) 
                        {
                            cout << rest << " is an invalid command" << endl;
                        }
                        else 
                        {
                            abMap.find(rest)->second->displayInfo();
                        }
                        //find the command at the key name, 
                        //second to get the value (the AbstractCommand *)
                        //displayInfo() called on the pointer to the AbstractCommand
                    }

                    else
                    {
                        //only one word
                        cout << first << " is an invalid command" << endl;
                    }
                }
                
                else
                {
                    //command name is the first word, not "help"
                    if (abMap.find(first) != abMap.end())
                    {
                        //command found
                        if (getline(s, rest))
                        {
                            //get everything after
                            rest = rest.substr(1, rest.length()); //get rid of the space in the beginning
                            abMap.find(first)->second->execute(rest);
                        }
                    }
                    else
                    {
                        //command not found
                        cout << first;
                        if (getline(s, rest))  //if there's a second word
                        {
                            cout << rest;  //print rest of the command
                        }
                        cout << " is an invalid command" << endl;
                    }
                }
            }
        }
    }
	return static_cast<int>(cpRet::success);
}


//lists all available commands 
//no parameters
//void return
void CommandPrompt::listCommands()
{
    map<string, AbstractCommand*>::iterator it;
    it = abMap.begin();
    while (it != abMap.end())
    {
        cout << it->first << endl; //print out name
        ++it;
    }
}


//prompt on the command line for input
//no parameters:
//return:
//  a string of what was inputted by the user
string CommandPrompt::prompt()
{
    cout  << "Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command." << endl;
    cout << "$   ";
    string str;

    getline(cin, str); //read in from line
	    
    return str;
}
