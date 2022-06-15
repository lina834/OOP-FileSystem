//Lab5.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors needed to construct the file system

#include "..\..\SharedCode\SimpleFileSystem.h"
#include "..\..\SharedCode\SimpleFileFactory.h"
#include "..\..\SharedCode\AbstractCommand.h"
#include "..\..\SharedCode\TouchCommand.h"
#include "..\..\SharedCode\CommandPrompt.h"
#include "..\..\SharedCode\CommandTest.h"
#include "..\..\SharedCode\LSCommand.h"
#include "..\..\SharedCode\CatCommand.h"
#include "..\..\SharedCode\RemoveCommand.h"
#include "..\..\SharedCode\DisplayCommand.h"
#include "..\..\SharedCode\CopyCommand.h"
#include "..\..\SharedCode\MacroCommand.h"
#include "..\..\SharedCode\RenameParsingStrategy.h"
#include "CatDSParsingStrategy.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
	AbstractFileSystem * afs = new SimpleFileSystem();
	AbstractFileFactory * aff = new SimpleFileFactory();
	
	//set up commands
	AbstractCommand * touch = new TouchCommand(afs, aff);
	AbstractCommand * ls = new LSCommand(afs);
	AbstractCommand * cat = new CatCommand(afs);
	AbstractCommand * rm = new RemoveCommand(afs);
	AbstractCommand * ds = new DisplayCommand(afs);
	AbstractCommand * cp = new CopyCommand(afs);

	//set up rename
	MacroCommand * rn = new MacroCommand(afs);
	AbstractParsingStrategy * rnParse = new RenameParsingStrategy();
	rn->addCommand(cp);
	rn->addCommand(rm);
	rn->setParseStrategy(rnParse);

	//set up catds (extra credit)
	MacroCommand * catds = new MacroCommand(afs);
	AbstractParsingStrategy * catdsParse = new CatDSParsingStrategy();
	catds->addCommand(cat);
	catds->addCommand(ds);
	catds->setParseStrategy(catdsParse);

	// AbstractCommand * catds = new CatDsCommand(afs);
	CommandPrompt commandPrompt;

	//adds command
	commandPrompt.setFileSystem(afs);
	commandPrompt.setFileFactory(aff);
	commandPrompt.addCommand("touch", touch);
	commandPrompt.addCommand("ls", ls);
	commandPrompt.addCommand("cat", cat);
	commandPrompt.addCommand("rm", rm);
	commandPrompt.addCommand("ds", ds);
	commandPrompt.addCommand("cp", cp);
	commandPrompt.addCommand("rn", rn);
	commandPrompt.addCommand("catds", catds);

	// commandPrompt.addCommand("catds", catds);
	commandPrompt.run();

	return 0;
}