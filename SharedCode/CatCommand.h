// CatCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of CatCommand

#pragma once

#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class CatCommand : public AbstractCommand
{
public:
    CatCommand(AbstractFileSystem * afs); 
    virtual int execute(std::string str); 
    virtual void displayInfo();
private:
    AbstractFileSystem * abFile;
};
 
//enum for constants used in in CatCommand
enum struct catNums
{
    endPart = 3
};