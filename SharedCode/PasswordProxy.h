// PasswordProxy.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of PasswordProxy

#pragma once 
#include "AbstractFile.h"
#include <string>
#include <vector>

class PasswordProxy : public AbstractFile{
public:
    PasswordProxy(AbstractFile * ab, std::string str);
    ~PasswordProxy();

    virtual std::vector<char> read(); 
	virtual int write(std::vector<char>);
	virtual int append(std::vector<char>);
	virtual unsigned int getSize();
	virtual std::string getName();
	
	virtual void accept(AbstractFileVisitor * abfv);
    virtual AbstractFile* clone(std::string);

protected:
    std::string passwordPrompt();
    bool passwordMatch(std::string str); //helper function
    
private:
    AbstractFile * abFile;
    std::string s;
};
