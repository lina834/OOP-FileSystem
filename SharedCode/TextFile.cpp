//TextFile.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for a text file

#include "TextFile.h" 
#include <iostream>
using namespace std;

//constructor
TextFile::TextFile(string s)
    :name(s){};

//create a copy of an image file
//parameters:
//  newName     the new name of the replicated file
//return:
//  a pointer to an abstract file that points to the replicated file
AbstractFile* TextFile::clone(string newName) 
{
    TextFile * cloneTF = new TextFile(*this);
    cloneTF->name = newName;
    return cloneTF;
}

//print out the file contents
//parameters:
//  abfv     the AbstractFileVisitor with the visit function
//void return
void TextFile::accept(AbstractFileVisitor * abfv)
{
    if (abfv) 
    {
        abfv -> visit_TextFile(this); 
    }
}

//return the contents of the file
//no parameters
//return:
//  the contents of the file
vector<char> TextFile::read()
{
    return vec;
}

//write to the file, overriding any previous content
//parameters:
//  inVec     a vector of characters to write in the file
//return values:
//  0   success
int TextFile::write(vector<char> inVec) 
{
    vec.clear(); //clears member variable, sets size to 0
    for (size_t i = 0; i < inVec.size(); ++i) 
    {
        vec.push_back(inVec[i]);
    }
    return static_cast<int>(ret::success);
}

//append to the file
//parameters:
//  inVec     a vector of characters to append to the file
//return values:
//	0   success
int TextFile::append(vector<char> inVec) 
{
    for (size_t i = 0; i < inVec.size(); ++i) 
    {
        vec.push_back(inVec[i]);
    }
    return static_cast<int>(ret::success);
}

//return the size of the file's contents
//no parameters
//return:
//  the size of the contents vector
unsigned int TextFile::getSize()
{
    unsigned int len = 0;
    for (size_t i = 0; i < vec.size(); ++i) 
    {
        ++len;
    }
    return len;
}

//return the name of the file
//no parameters
//return:
//  the name of the current file
string TextFile::getName()
{
    return name;
}