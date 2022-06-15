// AbstractFileFactory.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of abstract file factory
#pragma once
#include <string>
#include <string>
#include <string>
#include <string>
#include "AbstractFileSystem.h"

class AbstractFileFactory 
{
public:
	virtual AbstractFile * createFile(std::string) = 0;
};