// CommandPrompt.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of command prompt

#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include <map>
class CommandPrompt
{
public:
    CommandPrompt(); 
    void setFileSystem(AbstractFileSystem * a);
    void setFileFactory(AbstractFileFactory * a);  
    int addCommand(std::string s, AbstractCommand * ac);
    int run();
protected:
    void listCommands();
    std::string prompt();

private:
	std::map<std::string, AbstractCommand *> abMap; 
    AbstractFileSystem * abFile;
    AbstractFileFactory * abFileFac;
};

//return values for the command prompt class
enum struct cpRet
{
    success,
    quit,
    addCommand_failed
};