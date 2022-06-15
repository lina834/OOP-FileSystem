// MacroCommand.cpp
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to execute the macro command
#include "MacroCommand.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// constructor
MacroCommand::MacroCommand(AbstractFileSystem* afs) 
	:abFile(afs), aps(nullptr){}

// executes a macrocommand using the currrent parsing strategy 
// parameters:
// str     command line arguments to be passed to commands
// return values:
// 0    success
// 6	command_error
int MacroCommand::execute(string str) 
{
	//parse the input into a vector
	vector<string> vec = aps->parse(str);
	auto it = cmdVec.begin();
	int i = 0;
	
	// loops through to find the commands the MacroCommand is composed of
	while (it != cmdVec.end()) 
	{ 
		AbstractCommand* absCmd = *it;
		int result = absCmd->execute(vec[i]); // call the individual command’s execute function
		if (result != static_cast<int>(ret::success)) 
		{ 
			// return error if any command returns error
			return static_cast<int>(ret::command_error);
		}
		++i;
		++it;
	}
	// all commands executed successfully
	return static_cast<int>(ret::success);
}

// uses the parsing strategy to print out correct information about the macrocommand
// no parameters
// void return
void MacroCommand::displayInfo() 
{
	this->aps->info(); //info depends on the type of macrocommand, so we use the parsing strategy
}

//adds a command to the macrocommand
// parameters:
// 	aCmd	pointer to the command being added
//void return
void MacroCommand::addCommand(AbstractCommand* aCmd) 
{
	// add individual commands to the vector of commands
	this->cmdVec.push_back(aCmd);
}

//sets the parsing strategy to reflect the macrocommand's function
// parameters:
// 	p	pointer to the parsing strategy
//void return
void MacroCommand::setParseStrategy(AbstractParsingStrategy* p) 
{
	// set the macrocommand’s parsing strategy
	this->aps = p;
}