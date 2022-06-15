//LSCommand.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to execute the ls command
#include "LSCommand.h"
#include <map>
#include <string>
#include <sstream> 
#include <iostream>
#include "MetadataDisplayVisitor.h"
#include "BasicDisplayVisitor.h"
using namespace std;

//constructor
LSCommand::LSCommand(AbstractFileSystem * afs)
    :abFile(afs){}

//list all currently existing files
//parameters:
//  str     the name of the file being edited
//return values:
//  0   success    
int LSCommand::execute(string str)
{
    if (str == "-m")
    {
    	AbstractFileVisitor * visitor = new MetadataDisplayVisitor(); 
        
        //get a list of all files
        set<string> s = abFile -> getFileNames();

        auto it = s.begin();
        while (it != s.end())
        {
            AbstractFile* opened = abFile->openFile(*it); //obtain a pointer to the file
            opened->accept(visitor); //print out metadata 
            abFile->closeFile(opened);
            ++it;
        }
        return static_cast<int>(ret::success);
    }

    //get a list of all files
    set<string> s = abFile->getFileNames();
    
    //print it out
    auto it = s.begin();
    while (it!=s.end())
    {
        cout << *it; //first column

        //print out even spacing
        size_t spaces = 25 - (*it).length(); //PUT 25 IN A CONSTANT LATER
        for (size_t i = 0; i < spaces; ++i)
        {
            cout << " ";
        }

        ++it;
        // second column
        if (it != s.end()) 
        {
            //make sure there is a file to put in the second column
            cout << *it;
            ++it;
        }

        cout << endl;

    }

    return static_cast<int>(ret::success);

}

//information for ls command
void LSCommand::displayInfo()
{
        cout << "ls outputs to the terminal the names of all files currently in the file system" << endl;
        cout << "ls -m lists the file names with the metadata associated" << endl;
        cout << "Usage: ls or  ls -m" << endl;
}
