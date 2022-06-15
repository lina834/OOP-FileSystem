// LSCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of ls command and ls return values

#pragma once
#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class LSCommand : public AbstractCommand
{
public:
    LSCommand(AbstractFileSystem * afs);
    virtual int execute(std::string str);
    virtual void displayInfo();
private:
    AbstractFileSystem * abFile;
    AbstractFileFactory * abFac;
};


