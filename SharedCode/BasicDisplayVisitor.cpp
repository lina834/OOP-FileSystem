//BasicDisplayVisitor.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions for visitor for image/text files.

#include "BasicDisplayVisitor.h"
#include <iostream> 
using namespace std;

//prints out an image file in the proper format
//parameters:
//  img     a pointer to an image file being read in format
//void return
void BasicDisplayVisitor::visit_ImageFile(ImageFile* img)
{
    vector<char> c = img->read(); // read the characters of the image file
    unsigned int sqr = img->getSize(); //getSize() is for vector size. we need the range.
    unsigned int s = static_cast<int>(sqrt(sqr)); // to get the range, take the square root of the vector size.

    // print out in the proper layout
    for (int y = s - 1 ; y >= 0 ; --y) 
    { 
        for (unsigned int x = 0; x < s; ++x) 
        {
            int index = y * s + x;
            cout << c[index];
        }
        cout << endl;
    }
}


//prints out an text file in the proper format
//parameters:
//  txt     a pointer to the text file being read 
//void return
void BasicDisplayVisitor::visit_TextFile(TextFile* txt)
{
    vector<char> v = txt->read(); // read the characters of the text file
    // print out the characters 
    for (size_t i = 0; i < v.size(); ++i) 
    { 
      cout << v[i];
    }
    cout << endl;
}
 