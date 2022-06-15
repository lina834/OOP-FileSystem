// Studio18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "..\..\SharedCode\SimpleFileSystem.h"
#include "..\..\SharedCode\AbstractFileFactory.h"
#include "..\..\SharedCode\SimpleFileFactory.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	
	AbstractFileSystem * sysPtr = new SimpleFileSystem();
	AbstractFileFactory * facPtr = new SimpleFileFactory();
	
	sysPtr->addFile("test.img", facPtr->createFile("test.img"));
	
	AbstractFile * img = sysPtr->openFile("test.img");

	vector<char> writeIn;

	writeIn.push_back('X');
	writeIn.push_back(' ');
	writeIn.push_back('X');
	writeIn.push_back(' ');
	writeIn.push_back('X');
	writeIn.push_back(' ');
	writeIn.push_back('X');
	writeIn.push_back(' ');
	writeIn.push_back('X');
	writeIn.push_back('3');
	img->write(writeIn);
	img->read();

	sysPtr->addFile("test2.txt", facPtr->createFile("test2.txt"));
	AbstractFile * text = sysPtr->openFile("test2.txt");
	vector<char> writeIn2;
	writeIn2.push_back('1');
	writeIn2.push_back('2');
	writeIn2.push_back('3');
	writeIn2.push_back('4');
	
	text->write(writeIn2);
	text->read();

	writeIn2.push_back('5');
	text->write(writeIn2);
	text->read();

	return 0;
}