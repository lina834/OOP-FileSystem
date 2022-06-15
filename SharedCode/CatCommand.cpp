//CatCommand.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to execute the cat commmand

#include "CatCommand.h"
#include <map>
#include <string>
#include <sstream> 
#include <iostream>
#include "MetadataDisplayVisitor.h"
#include "BasicDisplayVisitor.h"
using namespace std;

//constructor
CatCommand::CatCommand(AbstractFileSystem * afs)
    :abFile(afs)
{} 

//write or append to a file
//parameters:
//  str     the name of the file being edited
//return values:
//  0   success
//  1   file_not_found,
//  9   input_line_error
//  10  file_dne
int CatCommand::execute(string str)
{
    if (str.length() == 0) //passed in an empty string
    { 
        return static_cast<int>(ret::input_line_error);
    }

    AbstractFileVisitor * abs = new BasicDisplayVisitor();

    //APPENDING
    if (str.substr(str.length() - static_cast<int>(catNums::endPart), str.length()) == " -a") //append function used
    { 
    	//AbstractFileVisitor * visitor = new MetadataDisplayVisitor(); 
        set<string> s = abFile -> getFileNames(); //get all file names
        string name = str.substr(0, str.length() - static_cast<int>(catNums::endPart)); //get the name of the file itself
       
        auto it = s.find(name); //iterator for the file 
        if(it != s.end())
        {
            //found in file system
            AbstractFile* opened = abFile->openFile(*it); //get a pointer to the opened file
            if (opened == nullptr)  // if the opened file is not valid
            {
                abFile->closeFile(opened);
                return static_cast<int>(ret::file_dne); // return a non-zero value
            }


            cout << name << endl; //print out the name of the file

            cout << "File contents:" << endl;
            opened->accept(abs); //print out file contents

            cout << "Enter data you'd like to append to the file. Enter \":wq\" to save and exit, enter \":q\" to exit without saving." << endl;
            string input; 
            vector<char> vec;
            while (getline(cin,input))
            {
                if (input == ":wq")
                {
                    vec.pop_back(); //removes the last \n char on the vector

                    //append it and quit this command
                    cout << ">> Appending to file. Please enter password if applicable. <<" << endl;
                    int result = opened->append(vec);
                    abFile->closeFile(opened); //close the file
                    
                    return result; //the error code of the append
                }

                if (input == ":q")
                {
                    abFile -> closeFile(opened); //close the file
                    
                    return static_cast<int>(ret::success); 
                }
                auto strIt = input.begin(); //iterator to go through the string
                while (strIt != input.end())
                {
                    vec.push_back(*strIt); //push back singular characters
                    ++strIt;
                }
                vec.push_back('\n'); //new line 
            }
            return static_cast<int>(ret::input_line_error);
        }
        //not found
        return static_cast<int>(ret::file_not_found);
    }

    //NOT APPENDING
    set<string> s = abFile->getFileNames(); //all file names
    auto it = s.find(str);
    if (it != s.end())
    {
        //found in file system
        AbstractFile* opened = abFile->openFile(*it); //get a pointer to the opened file
        
        if (opened == nullptr) // if the opened file is not valid
        { 
            abFile->closeFile(opened);
            return static_cast<int>(ret::file_dne); // return a non-zero value
        }

        cout << str << endl; //print out the name of the file, not the formatted output
        cout << "Enter data you'd like to write to the file. Enter \":wq\" to save the file and exit, enter \":q\" to exit without saving." << endl;
        
        string input; 
        vector<char> vec;
        while (getline(cin,input))
        {
            if (input == ":wq")
            {
                //append it and quit this command
                vec.pop_back(); //removes the last \n char on the vector

                cout << ">> Writing to file. Please enter password if applicable. <<" << endl;
                int result = opened->write(vec);
                abFile->closeFile(opened); //close the file
                
                return result; //the error code of the write
            }
            if (input == ":q")
            {
                abFile->closeFile(opened); //close the file
                
                return static_cast<int>(ret::success);
            }
            auto strIt = input.begin(); //iterator to go through the string
            while (strIt != input.end())
            {
                vec.push_back(*strIt); //push back singular characters
                ++strIt;
            }
            vec.push_back('\n'); //new line 
        }
        return static_cast<int>(ret::input_line_error);
    }
    //else not found
    return static_cast<int>(ret::file_not_found);
}

//information about cat
void CatCommand::displayInfo()
{
        cout << "cat allows you to write to a specific file." << endl;
        cout << "cat -a allows you to append to a specific file." << endl;
        cout << "Usage: cat <filename> or  cat <filename> -a" << endl;
}
