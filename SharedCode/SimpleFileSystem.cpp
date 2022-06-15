//SimpleFileSystem.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for a simple file system

#include "SimpleFileSystem.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <iostream>
using namespace std; 

//adds a file to the file system
//parameters:
//  s     the name of the file being added
// aPtr   the pointer to the file being added
//return values:
//  0   success  
//  2   null_file
//  3   file_already_exists
int SimpleFileSystem::addFile(string s, AbstractFile*aPtr)
{
    auto filesIt = files.find(s);
	if (filesIt == files.end())
    {
         // not found
		if (aPtr == nullptr)
        {
            return static_cast<int>(ret::null_file);
		}
        files.insert(pair<string, AbstractFile*>(s, aPtr));
        return static_cast<int>(ret::success);
    }
	else
    { // found
       return static_cast<int>(ret::file_already_exists);
	} 
}  

//get names of all currently existing files
//no parameters
//return:
//  a set of all file names
set<string> SimpleFileSystem::getFileNames()
{
    auto it = files.begin();
    set<string> s; 
    while (it != files.end()) 
    {
        s.insert(it->second->getName()); //put the name of the file into the the set
        ++it;
    }
    return s;
}  

//delete a file from the system
//parameters:
//  n     the name of the file being deleted
//return values:
//  0   success 
//  4   file_is_open
//  1   file_not_found
int SimpleFileSystem::deleteFile(string n)
{
    auto filesIt = files.find(n);
    if (filesIt != files.end()) 
    { 
        // found
        AbstractFile* f = filesIt->second; //get the pointer to the existing file 
        auto openF = openFiles.find(f);
        if (openF != openFiles.end()) 
        {
             // open
            return static_cast<int>(ret::file_is_open);
        }
        else 
        {
            files.erase(filesIt); //remove from set
            
            //avoid memory leaks
            delete f;
            f = nullptr; 

            return static_cast<int>(ret::success);
        }
    }
    //file has not been found in the system, can not be deleted
	return static_cast<int>(ret::file_not_found);
}

//opens a file from the system
//parameters:
//  n     the name of the file being opened
//return:
//  nullptr     nullptr if file can not be oepend
//  f   pointer to the file after opening
AbstractFile* SimpleFileSystem::openFile(string n)
{   
    auto filesIt = files.find(n);
	if (filesIt == files.end()) 
    { 
        // file doesn't exist
	    return nullptr;
    } 
    else 
    { 
        // file exists
        // check to ensure it's not already open
        AbstractFile * f = filesIt -> second; //get the pointer to the existing file 
        auto openF = openFiles.find(f);
        if (openF == openFiles.end()) 
        { 
            //not open
            //add file to set of open files
            openFiles.insert(f); 
            //return pointer to the file
            return f;
        } 
        else 
        { 
            return nullptr;
        }
    }
}


//closes a file
//parameters:
//  f     a pointer to the file being closed
//return values:
//  0   success 
//  5   file_not_open
int SimpleFileSystem::closeFile(AbstractFile* f)
{
    auto openF = openFiles.find(f);
    if (openF == openFiles.end()) 
    { 
        //not found
        return static_cast<int>(ret::file_not_open);
    }
    else 
    { 
        //found
        openFiles.erase(f);
        return static_cast<int>(ret::success);
    }
}
