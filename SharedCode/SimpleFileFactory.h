// SimpleFileFactor.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of SimpleFileFactory.h
#pragma once
#include <map>
#include <set>
#include "AbstractFileFactory.h"
#include "ImageFile.h"
#include "TextFile.h"

// Studio 18 - simplefilefactory class declaration goes here

enum struct simFileFac 
{
	equalStrings = 0,
	extension = 3
};

class SimpleFileFactory : public AbstractFileFactory 
{
public:
    virtual AbstractFile* createFile(std::string);
private:
    std::map<std::string, AbstractFile*> files; //contains all files in the file system  
    std::set<AbstractFile*> openFiles; //contains all files that are currently open
};
 
