//ImageFile.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// this source file has execute() and displayInfo() 
// This source file has functions and constructors that are needed for an ImageFile
#include "ImageFile.h"
#include <iostream>
using namespace std;

//constructor
ImageFile::ImageFile(string n)
    :name(n), size('0'){}
 
//create a copy of an image file
//parameters:
//  newName     the new name of the replicated file
//return:
//  a pointer to an abstract file that points to the replicated file
AbstractFile* ImageFile::clone(string newName) 
{
    ImageFile * cloneIF = new ImageFile(*this);
    cloneIF->name = newName;
    return cloneIF;
}

//print out the file contents
//parameters:
//  abfv     the AbstractFileVisitor with the visit function
//void return
void ImageFile::accept(AbstractFileVisitor * abfv)
{
    if (abfv) 
    {
        abfv -> visit_ImageFile(this);
    }
}

//return the size of the file's contents
//no parameters
//return:
//  the size of the contents vector
unsigned int ImageFile::getSize()
{
    return static_cast<int>(contents.size());
} 

//return the name of the file
//no parameters
//return:
//  the name of the current file
string ImageFile::getName()
{
    return name;
}

//write to the file, overriding any previous content
//parameters:
//  vec     a vector of characters to write in the file
//return values:
//  0   success
//	13   can_not_write
int ImageFile::write(vector<char> vec)
{
    //set the size to the size given
    char vecSize = vec[vec.size()-1];  
    size = vecSize; 
    int invalid = 0;

    contents.clear(); //clear out old content

    //go through the given character vector
    for (size_t i = 0; i < vec.size()-imageSizePosition; ++i) 
    {
        if (vec[i] != 'X' && vec[i] != ' ')
        {
            ++invalid;
        }
        else 
        {
            //if a valid character, push to the contents
            contents.push_back(vec[i]);
        }
    }
    
    int sizeInt = vecSize - '0'; //get the size given in the vector
    
    //if: either there are invalid characters OR the given size does not match the actual size of the vector
    //then: clear out the entire contents vector
    if (invalid > 0 || static_cast<size_t>(sizeInt * sizeInt) != contents.size())
    { // one character taken away for the new line
        contents.clear();
        size = '\0';
        return static_cast<int>(ret::can_not_write);
    }
    
    return static_cast<int>(ret::success);
}

//append to the file. You can not append to an image file.
//parameters:
//  vec     a vector of characters to append to the file
//return values:
//	16   file_not_supported
int ImageFile::append(vector<char> vec)
{
    cout << "You can not append to an image file." << endl;
    return static_cast<int>(ret::file_not_supported);
}

//return the contents of the file
//no parameters
//return:
//  the contents of the file
vector<char> ImageFile::read()
{
    return contents;
}
