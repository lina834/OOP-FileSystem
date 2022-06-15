// DisplayCommand.cpp
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// this source file has execute() and displayInfo() 
// execute() is responsible for executing ds command
// displayInfo() is reponsible for providing usage information about ds command

#include "DisplayCommand.h"
#include <iostream>
#include <istream>
#include <sstream>
using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* afs)
    :abFile(afs) {}

// displays a file
// parameters:
// str     the name of the file being copied
// return values:
// 0    success
// 10   fine_dne
int DisplayCommand::execute(std::string str)
{
    if (str.length() == 0)
    { //passed in an empty string
        return static_cast<int>(ret::file_dne);
    }

    // UNFORMATTED
    if (str.substr(str.length() - static_cast<int>(dsNums::endPart), str.length()) == " -d") 
    { 
        // if the command is ds <filename> -d  
        set<string> s = abFile->getFileNames(); //get all file names
        string fileName = str.substr(0, str.length() - static_cast<int>(dsNums::endPart)); //get the name of the file itself, without ' -d'

        auto it = s.find(fileName); // iterate over the set to find the file
        if (it != s.end()) 
        { 
            //found in the file system 
            AbstractFile* openedfile = abFile->openFile(*it); //get a pointer to the opened file

            if (openedfile == nullptr) 
            {
                // check if the opened file is valid 
                abFile->closeFile(openedfile);
                return static_cast<int>(ret::file_dne); 
            }
            string type = fileName.substr(fileName.size() - static_cast<int>(dsNums::endPart)); // extracting the type of the file (img or txt)

            // unformatted ds for image files
            if (type.compare("img") == static_cast<int>(dsNums::equalStrings)) 
            { 
                vector<char> vtr = openedfile->read(); // read() to read the data
                string toString(vtr.begin(), vtr.end()); //vector indices are converted to string 
                istringstream iss(toString);  
                cout << iss.str() << endl;  // print out the raw data
                abFile->closeFile(openedfile); // close the file
                return static_cast<int>(ret::success); 
            }

            // unformatted ds for text files
            AbstractFileVisitor* visitor = new BasicDisplayVisitor(); 
            openedfile->accept(visitor); 
            abFile->closeFile(openedfile);
            return static_cast<int>(ret::success);
        }

        
    }


    // if not -d | FORMATTED
	set<string> s = abFile->getFileNames();
    auto it = s.find(str); // iterator to find the file from the set
    if (it != s.end()) 
    { 
        //found in the file system
        AbstractFile * openedFile = abFile->openFile(str);  // obtain the pointer to the file
        if (openedFile == nullptr) 
        { 
            // check if the opened file is valid 
            abFile->closeFile(openedFile); 
            return static_cast<int>(ret::file_dne); // if invalid, return a non-zero value
        }
        AbstractFileVisitor* visitor = new BasicDisplayVisitor();
        openedFile->accept(visitor); // accept() reads img/txt files in format
        abFile->closeFile(openedFile);  
        return static_cast<int>(ret::success);  // return success
    }
        
    return static_cast<int>(ret::file_dne); //otherwise, return a nonzero value
}

//info about display command
void DisplayCommand::displayInfo()
{
    cout << "ds opens a file and displays its contents in format" << endl;
    cout << "ds -a opens a file and displays its data only" << endl;
    cout << "Usage:  ds <filename>  or  ds <filename> -d" << endl;
}
