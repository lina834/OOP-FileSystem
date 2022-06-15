// RenameParsingStrategy.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of rn command and rn return values.
#pragma once

#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "AbstractParsingStrategy.h"

class RenameParsingStrategy : public AbstractParsingStrategy 
{
public:
    virtual std::vector<std::string> parse(std::string str);
    virtual void info(); //added due to extra credit
};
