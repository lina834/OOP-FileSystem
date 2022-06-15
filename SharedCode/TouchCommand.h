// TouchCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of touch command 
#pragma once
#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

// class AbstractFileSystem;
// class AbstractFileFactory;

class TouchCommand : public AbstractCommand 
{
public:
    TouchCommand(AbstractFileSystem * afs, AbstractFileFactory * aff);
    virtual int execute(std::string);
    virtual void displayInfo();    
private:
    AbstractFileSystem * abFile;
    AbstractFileFactory * abFac;
};


enum struct touchNums 
{
    endPart = 3
};