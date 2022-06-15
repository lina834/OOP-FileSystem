// Studio17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "..\..\SharedCode\AbstractFile.h"
#include "..\..\SharedCode\ImageFile.h"
#include <iostream>

using namespace std;


int main()
{
	AbstractFile * abFile;
	ImageFile image("image");
	abFile = & image; 

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

	image.write(writeIn);
	image.read();
	
	
	return 0;
}

