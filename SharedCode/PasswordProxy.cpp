//PasswordProxy.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for a PasswordProxy

#include "PasswordProxy.h"
#include <iostream>
#include <string> 

using namespace std;

//constructor
PasswordProxy::PasswordProxy(AbstractFile * ab, string str)
    :abFile(ab), s(str){ }

//destructor
PasswordProxy::~PasswordProxy()
{
    //no hanging pointers or memory leaks
    abFile = nullptr; 
    delete abFile;
}

//create a copy of a proxy file
//parameters:
//  newName     the new name of the replicated file
//return:
//  a pointer to an abstract file that points to the replicated file
AbstractFile* PasswordProxy::clone(string newName) 
{
    AbstractFile * clonePP = new PasswordProxy(abFile->clone(newName), s);
    return clonePP;
}

//return the contents of the file
//no parameters
//return:
//  the contents of the file if correct passsword
//  empty vector if incorrect password
vector<char> PasswordProxy::read()
{
    if (passwordMatch(passwordPrompt()))
    { 
        //password matches
        return abFile -> read();
    }
    cout << "incorrect password" << endl;
    return std::vector<char>();
}

//write to the file, overriding any previous content
//parameters:
//  vc     a vector of characters to write in the file
//return values:
//  the return value from the write() called by the file using the proxy if correct password
//  14   wrongPassword
int PasswordProxy::write(vector<char> vc)
{
    if (passwordMatch(passwordPrompt()))
    {
        //password matches
        return abFile -> write(vc);
    }
    cout << "incorrect password" << endl;
    return static_cast<int>(ret::wrongPassword);
}

//append to the file
//parameters:
//  vc     a vector of characters to write in the file
//return values:
//  the return value from the append() called by the file using the proxy if correct password
//  14   wrongPassword
int PasswordProxy::append(vector<char> vc)
{
    if (passwordMatch(passwordPrompt())) 
    {
        return abFile->append(vc);
    }
    cout << "incorrect password" << endl;
    return static_cast<int>(ret::wrongPassword);
}

//return the size of the file's contents
//no parameters
//return:
//  the size of the contents vector
unsigned int PasswordProxy::getSize()
{
    return abFile->getSize();
}

//return the name of the file
//no parameters
//return:
//  the name of the current file
std::string PasswordProxy::getName()
{
    return abFile->getName();
}

//print out the file contents if the password is correct
//parameters:
//  abfv     the AbstractFileVisitor with the visit function
//void return
void PasswordProxy::accept(AbstractFileVisitor* abfv)
{
    if (passwordMatch(passwordPrompt())) 
    {
        abFile->accept(abfv);
    }
}

//prompt the user for a password
//no parameters
//return the password entered
string PasswordProxy::passwordPrompt()
{
    cout << "Password:" << endl;
    string pass;
    getline(cin, pass);
    return pass;
}

//helper function that checks the given string with the password for the file
//parameters:
//  str     the password given to check
//return:
//  true if str matches the password; otherwise, false
bool PasswordProxy::passwordMatch(string str)
{
    return str == s;
}
