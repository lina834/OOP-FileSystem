// CopyCommand.cpp
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// this source file has execute() and displayInfo() 
// execute() is responsible for executing cp command
// displayInfo() is reponsible for providing usage information about cp command

#include "CopyCommand.h"
#include <iostream>
using namespace std;

//constructor
CopyCommand::CopyCommand(AbstractFileSystem* afs)
    :abFile(afs){}

// creates a copy of a file
// parameters:
// str     the name of the file being copied
// return values:
// 0    success
// 10   fine_dne
// 11   unable_to_copy
// 12   arg_error
int CopyCommand::execute(string str)
{
    if(str.length() == 0)
    { 
        //passed in an empty string
        return static_cast<int>(ret::arg_error);
    }

    istringstream iss(str);
    string og_file; // string to take in filename to be copied
    string new_filename; // string to take in new filename for the copy

    if (iss >> og_file) 
    { 
        // first argument -> original filename
        if (iss >> new_filename) 
        {
            // secound argument -> new filename
            //if more than 2 arguments, 
            string extra;
            if (iss >> extra) 
            {
                return static_cast<int>(ret::arg_error); // return non-zero return value
            }

            // if all arguments are valid: 
            set<string> s = abFile->getFileNames(); // get all filenames from the file system

            // extracting the type of the file (img or txt), and add the extension to the new name. 
            string type = og_file.substr(og_file.size() - static_cast<int>(cpNums::endPart)); 
            if (type.compare("img") == static_cast<int>(cpNums::equalStrings)) 
            { 
                new_filename = new_filename + ".img"; 
            }
            else 
            {
                new_filename = new_filename + ".txt";
            }


            auto it = s.find(og_file); // iterator to find the file

            if (it != s.end()) 
            { 
                //found in the file system 
                AbstractFile* openedFile = abFile->openFile(og_file); // pointer to opened file (original copy)

                if (openedFile == nullptr) 
                {
                    // if the opened file is not valid
                    abFile->closeFile(openedFile);
                    return static_cast<int>(ret::file_dne); // return a non-zero value
                }
                
                // if opened file is valid, 
                AbstractFile* copy = openedFile->clone(new_filename); // call clone() to the opened file. 
                                                                      // it returns the pointer to a copy file.

                if (copy == nullptr) 
                { 
                    // if the copied file is not valid
                    abFile->closeFile(openedFile);
                    abFile->closeFile(copy);
                    delete copy; // avoid memory leaks
                    return static_cast<int>(ret::unable_to_copy); // return a non-zero value
                }
                
                if (abFile->addFile(new_filename, copy) != static_cast<int>(ret::success)) 
                { 
                    // if not added correctly to the file system
                    abFile->closeFile(openedFile);
                    abFile->closeFile(copy);  // avoid memory leaks
                    return static_cast<int>(ret::unable_to_copy); // return a non-zero value
                }
                
                // Otherwise, copy is made successfully.
                abFile->closeFile(openedFile); 
                abFile->closeFile(copy);
                return static_cast<int>(ret::success);
            }
            
        }
        
    }

   
    return static_cast<int>(ret::file_dne); //otherwise, return a nonzero value
}


//display info for copy command
void CopyCommand::displayInfo()
{
    cout << "cp copies a file that exists in the file system and add the copy to the file system with a different name." << endl;
    cout << "Usage: cp <file_to_copy> <new_name_with_no_extension>" << endl;
}
