// AbstractParsingStrategy.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of abstract parsing strategy.

#pragma once

class AbstractParsingStrategy 
{
public:
	virtual std::vector<std::string> parse(std::string str) = 0;
	virtual void info() = 0; //added due to extra credit
};
