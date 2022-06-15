// CatDSParsingStrategy.cpp
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu

#include <iostream>
#include <sstream> 
#include "CatDSParsingStrategy.h"
#include "..\..\SharedCode\CatCommand.h"
#include "..\..\SharedCode\RemoveCommand.h"
using namespace std;

//parses a string to pass to the cat and ds commnd
// parameters: 
//  str     the command line to be parsed
// return:
//      vector that has a file name to be used in cat/ds command
vector<string> CatDSParsingStrategy::parse(string str) {
    vector<string> output;
    string fileName;
    istringstream iss(str);     
    iss >> fileName; 
    output.push_back(fileName);
    output.push_back(fileName);
    
    return output;

}

//displays information about the catds command
//no parameters
//void return
void CatDSParsingStrategy::info(){
    cout << "catds allows you to overwrite a file and displays the contents after." << endl;
    cout << "Usage: catds <filename>" << endl;
}