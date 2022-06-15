// CatDSParsingStrategy.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of cat ds command and cat ds return values.
#pragma once

#include "..\..\SharedCode\AbstractFile.h"
#include "..\..\SharedCode\AbstractCommand.h"
#include "..\..\SharedCode\AbstractFileSystem.h"
#include "..\..\SharedCode\AbstractFileFactory.h"
#include "..\..\SharedCode\AbstractParsingStrategy.h"

class CatDSParsingStrategy : public AbstractParsingStrategy {
public:
    virtual std::vector<std::string> parse(std::string str);
    virtual void info(); //added due to extra credit
};
