// MetadataDisplayVisitor.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of MetadataDisplayVisitor 
#pragma once
#include "AbstractFileVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"

//constants needed in this class
enum struct metaConst{
    spaceBetween = 25,
    fiveSpaces = 5,
    sixSpaces = 6
};

class MetadataDisplayVisitor : public AbstractFileVisitor {
    virtual void visit_ImageFile(ImageFile* img);
    virtual void visit_TextFile(TextFile* txt); 
};  