//MetadataDisplayVisitor.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed for a metadisplay visitor

#include "MetadataDisplayVisitor.h"
#include <iostream>

using namespace std;

//print out name, type, and size of an image file
//parameters:
//  img     a pointer to the text file being edited
//void return
void MetadataDisplayVisitor::visit_ImageFile(ImageFile * img) 
{
    cout << img->getName();
    //calculate how many spaces needed
    size_t spaceEven = static_cast<int>(metaConst::spaceBetween) - img->getName().length();
    
    //print out in even spacing
    for (size_t i = 0; i < spaceEven; ++i)
    {
        cout << " ";
    }
    cout << "image"; //type of file
    
    //five spaces before size
    for (int i = 0; i < static_cast<int>(metaConst::fiveSpaces); ++i) 
    { 
        cout << " ";
    }
    cout << img->getSize() << endl;
}

//print out name, type, and size of a text file
//parameters:
//  txt     a pointer to the text file being edited
//void return
void MetadataDisplayVisitor::visit_TextFile(TextFile * txt)
{
    cout << txt->getName();
    //calculate how many spaces needed
    size_t spaceEven = static_cast<int>(metaConst::spaceBetween) - txt->getName().length(); 
    
    //print out in even spacing
    for (size_t i = 0; i < spaceEven; ++i)
    {
        cout << " ";
    }
    cout << "text"; //type of file
    
    //six spaces before size
    for (int i = 0; i < static_cast<int>(metaConst::sixSpaces); ++i) 
    {
        cout << " ";
    }
    cout << txt->getSize() << endl;
    
}  