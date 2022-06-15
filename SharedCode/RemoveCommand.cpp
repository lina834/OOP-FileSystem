// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// this source file has execute() and displayInfo() 
// execute() is responsible for executing rm command
// displayInfo() is reponsible for providing usage information about rm command
#include "RemoveCommand.h"
#include <map>
#include <sstream> 
#include <iostream>
#include "MetadataDisplayVisitor.h"
#include "BasicDisplayVisitor.h"

using namespace std;

//constructor
RemoveCommand::RemoveCommand(AbstractFileSystem* afs)
    :abFile(afs) {
}

// removes a file
// parameters:
// str     the name of the file being removed
// return values:
// 0    success
// 10   file_dne
// 15   unable_to_rm
int RemoveCommand::execute(string str)
{
	set<string> s = abFile->getFileNames();
    auto it = s.begin();
    while (it != s.end())
    { 
        //loops through to find the file 
        if (*it == str) 
        {
             // if it finds the matching file, it deletes it from the file system
            int result = abFile->deleteFile(str);

            //found it but was not deleted in the file system correctly
            if (result != static_cast<int>(ret::success))
            {
                return  static_cast<int>(ret::unable_to_rm);
            }
            // successfully deleted from the file system
            return static_cast<int>(ret::success);
        }
        ++it;
    }
        
    return static_cast<int>(ret::file_dne); //otherwise, return a nonzero value
}

//info about remove command
void RemoveCommand::displayInfo()
{
    cout << "rm allows you to remove a specific file." << endl;
    cout << "Usage: rm <filename>" << endl;
}
