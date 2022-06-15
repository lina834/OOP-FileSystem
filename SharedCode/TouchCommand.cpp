//TouchCommand.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for touch command
#include "TouchCommand.h"
#include "AbstractFile.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "PasswordProxy.h"

#include <iostream>
using namespace std;

//constructor
TouchCommand::TouchCommand(AbstractFileSystem* afs, AbstractFileFactory* aff)
    :abFile(afs), abFac(aff)
    {}
 

// creates a new file - img or txt
// parameters:
// str     the name of the file being created. last three characters are extension
// return values:
// 0    success
// 7    file_not_created 
// 8    file_not_added
int TouchCommand::execute(string str)
{
    if (str.length() == 0) 
    { 
        //passed in an empty string
        return static_cast<int>(ret::file_not_created);
    }

    //password protected
    if (str.substr(str.length() - static_cast<int>(touchNums::endPart), str.length()) == " -p") 
    {
        string name = str.substr(0, str.length() - static_cast<int>(touchNums::endPart));
      
        AbstractFile * file = abFac->createFile(name); //create the file
        if (file!=nullptr) 
        {
            //file created successfully

            //get password
            cout << "What is the password?" << endl;
            string password;
            getline(cin, password); 

            //create proxy + add it to the file system
            AbstractFile* p = new PasswordProxy(file, password);
            int result = abFile->addFile(name, p);

            // file was created successfully but was not added to the file system correctly
            if (result != static_cast<int>(ret::success)) { 
                // delete result
                delete file;
                file = nullptr;
                
                cout << "File could not be created." << endl;
                return static_cast<int>(ret::file_not_added);
            }
            return static_cast<int>(ret::success);
        } 
        else 
        { // if file was not created successfully
            cout << "File could not be created." << endl;
            return static_cast<int>(ret::file_not_created);
        }
    }

    //else, not password protected:

    AbstractFile * file = abFac->createFile(str); //create the file
    if (file!=nullptr) 
    {
        //file created successfully
        //add the file to the file system
        int result = abFile->addFile(str, file);
        // file was created successfully but was not added to the file system correctly
        if (result != static_cast<int>(ret::success)) 
        { 
            // delete result; 
            delete file;
            file = nullptr;

            cout << "File could not be created." << endl;
            return static_cast<int>(ret::file_not_added);
        }
        return static_cast<int>(ret::success);
    } 
    else 
    { 
        // if file was not created successfully
        cout << "File could not be created." << endl;
        return static_cast<int>(ret::file_not_created);
    }
}

//displays info about touch command
//no parameters
//void return
void TouchCommand::displayInfo()
{
    cout << "touch creates a file." << endl;
    cout << "touch -p creates a password protected file." << endl;
    cout<< "usage: touch <filename> or touch <filename> -p" << endl;
}
