// AbstractFileVisitor.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of abstract file visitor
#pragma once
class ImageFile;
class TextFile;

class AbstractFileVisitor 
{
public:
    virtual void visit_ImageFile(ImageFile * img) = 0;
    virtual void visit_TextFile(TextFile * txt) = 0;
}; 