// RemoveCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of rm command and rm return values.
#pragma once
#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class RemoveCommand : public AbstractCommand 
{
public:
    RemoveCommand(AbstractFileSystem* afs);
    virtual int execute(std::string str);
    virtual void displayInfo();
private:
    AbstractFileSystem* abFile;
};



