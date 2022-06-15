// AbstractFile.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of abstract file and return values of the program.

#pragma once
#include <vector>
#include <string>
class AbstractFileVisitor;


class AbstractFile 
{
public:
	virtual std::vector<char> read() = 0; 
	virtual int write(std::vector<char>) = 0;
	virtual int append(std::vector<char>) = 0;
 	virtual unsigned int getSize() = 0;
	virtual std::string getName() = 0;
	virtual AbstractFile* clone(std::string) = 0; //for copy command
	virtual void accept(AbstractFileVisitor * abfv) = 0;
};   


//enum for all return values
enum struct ret 
{
	success, //0
	file_not_found, //1
	null_file, //2
	file_already_exists, //3
	file_is_open, //4
	file_not_open, //5
	command_error, //6
	file_not_created, //7
	file_not_added, //8
	input_line_error, //9
	file_dne, //10
	unable_to_copy, //11
	arg_error, //12
	can_not_write, //13
	wrongPassword, //14
	unable_to_rm, //15
	file_not_supported //16
};