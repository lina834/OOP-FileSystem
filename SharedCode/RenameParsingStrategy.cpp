// MacroCommand.cpp
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has a function that is needed to execute the rename parsing strategy
#include <iostream>
#include <sstream> 
#include "RenameParsingStrategy.h"
#include "CopyCommand.h"
#include "RemoveCommand.h"
using namespace std;

// parses a string to pass to the copy and remove files
// parameters:
// str     the command line to be parsed
// return:
//      vector that has a file name to be used in cp/rm command
vector<string> RenameParsingStrategy::parse(string str) 
{
    
    istringstream iss(str); //separates file names by whitespace
    string existingFile, newName;
    iss >> existingFile >> newName; // separate into the existing file name and new name
    string idxZero;
    idxZero = existingFile + " " + newName; 
    vector<string> output;
    output.push_back(idxZero);
    output.push_back(existingFile);
    // return a vector containing the strings
    return output;

}

//displays information about the catds command
//no parameters
//void return
void RenameParsingStrategy::info()
{
    cout << "rn renames a file." << endl;
    cout << "Usage: rn <existing_file> <new_name>" << endl;
}