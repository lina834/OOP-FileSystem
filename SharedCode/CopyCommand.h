// CopyCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of cp command and cp return values.

#pragma once
#include "BasicDisplayVisitor.h"
#include "MetadataDisplayVisitor.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "ImageFile.h"
#include "TextFile.h"
#include <string>
#include <sstream> 

class CopyCommand : public AbstractCommand 
{
public:
    CopyCommand(AbstractFileSystem* afs);
    virtual int execute(std::string str);
    virtual void displayInfo();
  
private:
    AbstractFileSystem* abFile;
};

//constants used in copy command
enum struct cpNums 
{
    equalStrings = 0,
    endPart = 3
};