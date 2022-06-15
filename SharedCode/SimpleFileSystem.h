#pragma once
// declaration of SimpleFileSystem class goes here
#include "AbstractFileSystem.h"
#include <map>
#include <set>
#include <string>



enum fileNameConst 
{
	equalStrings = 0,
	extension = 3
};

class SimpleFileSystem : public AbstractFileSystem 
{
public: 
    virtual int addFile(std::string, AbstractFile*); 
	//virtual int createFile(std::string); //commented out studio 18
	virtual int deleteFile(std::string);
	virtual AbstractFile* openFile(std::string);
	virtual int closeFile(AbstractFile*);
	virtual std::set<std::string> getFileNames();
private:
	std::map<std::string, AbstractFile*> files; //contains all files in the file system  
    std::set<AbstractFile*> openFiles; //contains all files that are currently open
};  