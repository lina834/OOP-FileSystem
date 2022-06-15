// Studio16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\AbstractFile.h"
#include <iostream>

using namespace std;


int main()
{
	AbstractFile * abFile;
	TextFile text("testing title");

	abFile = & text;
	
	vector<char> writeIn;
	
    
	writeIn.push_back('1');
	
	abFile -> write(writeIn);
	
	cout << "first read" <<endl;

	abFile -> read();

	cout << endl;

	vector<char> appendIn;
	appendIn.push_back('0');
	
	abFile -> append(appendIn);
	abFile -> read();

	abFile -> write(writeIn);
	abFile -> read();

	return 0;

}
