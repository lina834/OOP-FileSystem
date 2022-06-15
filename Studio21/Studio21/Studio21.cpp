// Studio21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "..\..\SharedCode\SimpleFileSystem.h"
#include "..\..\SharedCode\SimpleFileFactory.h"
#include "..\..\SharedCode\AbstractCommand.h"
#include "..\..\SharedCode\TouchCommand.h"
#include "..\..\SharedCode\CommandPrompt.h"
#include "..\..\SharedCode\CommandTest.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
	AbstractFileSystem * afs = new SimpleFileSystem();
	AbstractFileFactory * aff = new SimpleFileFactory();
	
	AbstractCommand * tc = new TouchCommand(afs, aff);

	CommandPrompt cp;
	cp.setFileSystem(afs);
	cp.setFileFactory(aff);
	cp.addCommand("tc", tc);


	cp.run();

	return 0;
}

