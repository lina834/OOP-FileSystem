// MacroCommand.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of MacroCommand and MacroCommand return values.
#pragma once
#include "AbstractFile.h"
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "AbstractParsingStrategy.h"

class MacroCommand : public AbstractCommand {
public:
	MacroCommand(AbstractFileSystem* afs);
	virtual int execute(std::string str);
	virtual void displayInfo();
	void addCommand(AbstractCommand* aCmd);
	void setParseStrategy(AbstractParsingStrategy* p);
private:
	AbstractFileSystem* abFile;
	std::vector<AbstractCommand*> cmdVec;
	AbstractParsingStrategy* aps;
};


