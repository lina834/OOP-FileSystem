// ImageFile.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of ImageFile 
#pragma once
#include <string>
#include <vector> 
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"

//constants for image file attributes
const int imageSizePosition = 1;


class ImageFile : public AbstractFile 
{
public:
	ImageFile(std::string);
	virtual unsigned int getSize();
	virtual std::string getName();
	virtual int write(std::vector<char>);
	virtual int append(std::vector<char>);
	virtual std::vector<char> read();
	virtual void accept(AbstractFileVisitor * abfv);
	virtual AbstractFile* clone(std::string);
private:
	std::string name;
	std::vector<char> contents;
	char size;
};  