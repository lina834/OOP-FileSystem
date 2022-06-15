// BasicDisplayVisitor.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of basic display visitor
#pragma once
#include "ImageFile.h"
#include "TextFile.h"


class BasicDisplayVisitor : public AbstractFileVisitor 
{
public:
    virtual void visit_ImageFile(ImageFile * img);
    virtual void visit_TextFile(TextFile * txt);
};  