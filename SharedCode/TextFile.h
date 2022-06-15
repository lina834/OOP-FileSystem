// TextFile.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of TextFile 
#pragma once
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"

class TextFile : public AbstractFile 
{
private:
	std::vector<char> vec;
	std::string name;

public:
    TextFile(std:: string s);

    virtual std::vector<char> read(); 
	virtual int write(std::vector<char>);
	virtual int append(std::vector<char>);
	virtual unsigned int getSize();
	virtual std::string getName(); 
	virtual void accept(AbstractFileVisitor * abfv);
	virtual AbstractFile* clone(std::string);
};



