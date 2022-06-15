// DisplayCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of ds command and ds return values
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

class DisplayCommand : public AbstractCommand 
{
public:
    DisplayCommand(AbstractFileSystem* afs);
    virtual int execute(std::string str);
    virtual void displayInfo();
private:
    AbstractFileSystem* abFile;
};

enum struct dsNums 
{
    equalStrings = 0,
    endPart = 3
};