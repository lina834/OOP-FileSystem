//SimpleFileFactory.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for a simple file factory

#include "SimpleFileFactory.h"
#include <string>
#include <iostream>

using namespace std;

//create a file
//parameters:
//  n    the name of the file being created
//return:
//  nullptr  if the name of the file isn't of a valid extension
//  textfile   a pointer to a new textfile with the given name
//  imgFile    a pointer to a new image file with the given name
AbstractFile * SimpleFileFactory::createFile(string n)
{
    if (n.size() < static_cast<int>(simFileFac::extension))
    { 
        //.txt or .img
        return nullptr;
    }

    string type = n.substr(n.size()- static_cast<int>(simFileFac::extension)); //enum in SimpleFileFactory.h

    if (type.compare("txt") == static_cast<int>(simFileFac::equalStrings)) 
    {
        TextFile * textFile = new TextFile(n);
        return textFile;
    }
    
    if (type.compare("img") ==  static_cast<int>(simFileFac::equalStrings)) 
    {
        ImageFile * imgFile = new ImageFile(n);
        return imgFile;
    }
    
    return nullptr;
} 