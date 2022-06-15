// AbstractFileSystem.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of abstract file system
#pragma once
#include <string>
#include "AbstractFile.h"
#include <set>

class AbstractFileSystem 
{
public:
	virtual int addFile(std::string, AbstractFile*) = 0; 
	virtual int deleteFile(std::string) = 0;
	virtual AbstractFile* openFile(std::string) = 0;
	virtual int closeFile(AbstractFile*) = 0;
	virtual std::set<std::string> getFileNames() = 0;
	virtual ~AbstractFileSystem() = default; // virtual destructor 
}; 