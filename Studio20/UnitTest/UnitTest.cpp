#include "pch.h"
#include "CppUnitTest.h"

#define protected public

#include "../../SharedCode/TextFile.cpp"
#include "../../SharedCode/ImageFile.cpp"
#include "../..//SharedCode/SimpleFileFactory.cpp"
#include "../../SharedCode/SimpleFileSystem.cpp"
#include "../../SharedCode/BasicDisplayVisitor.cpp"
#include "../../SharedCode/MetadataDisplayVisitor.cpp"
#include "../../SharedCode/PasswordProxy.cpp"

#undef protected

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(textFile)
	{
	public:
		/*
		// checks that the file is initialized with proper name and size,
		// expects size to be 0 and the name to match the input to the constructor
		*/
		TEST_METHOD(contstructor)
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.txt";
			unsigned int fileSize = 0;
			TextFile t(fileName);
			Assert::AreEqual(fileName, t.getName());
			Assert::AreEqual(fileSize, t.getSize());
		}
		TEST_METHOD(write) // tests write, expects that the function returns success and that the size of the file is updated correctly
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), t.getSize());

		}
		TEST_METHOD(append) // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			unsigned int fileSize = t.getSize();
			Assert::AreEqual(0, t.append(v));
			Assert::AreEqual(static_cast<unsigned int>(fileSize + v.size()), t.getSize());

		}
		TEST_METHOD(read) // tests that the read function outputs the contents of the file
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			std::vector<char> contents = t.read();
			Assert::AreEqual(v.size(), (size_t)t.getSize());
			Assert::AreEqual(v.size(), contents.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(contents[i], v[i]);
			}
		}
		TEST_METHOD(readWithAppend) // tests that read also works with appending to a file
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			Assert::AreEqual(0, t.append(v));
			std::vector<char> newExpectedV = { 'h', 'i',  'h', 'i' };
			std::vector<char> contents = t.read();
			Assert::AreEqual(static_cast<unsigned int>(newExpectedV.size()), t.getSize());
			Assert::AreEqual(newExpectedV.size(), contents.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(contents[i], newExpectedV[i]);
			}

		}
	};

	TEST_CLASS(imageFile)
	{
	public:

		TEST_METHOD(contstructor) // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			Assert::AreEqual(fileName, t.getName());
			Assert::AreEqual(fileSize, t.getSize());
		}
		TEST_METHOD(writeValid) // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size() - 1), t.getSize());
		}
		TEST_METHOD(writeSizeMismatch) // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', 4 };
			Assert::AreNotEqual(0, t.write(v)); // non-zero error returned
			Assert::AreEqual(fileSize, t.getSize()); // contents not added
		}
		TEST_METHOD(writeInvalidPixel) // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', 3 };
			Assert::AreNotEqual(0, t.write(v));
			Assert::AreEqual(fileSize, t.getSize()); // contents not added
		}
		TEST_METHOD(appendInvalid) // tests that append returns a non-zero value (can't append to an image)
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert::AreNotEqual(0, t.append(v)); // can't append to image
		}
		TEST_METHOD(read) // tests that read returns the contents that are written to the file
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			std::vector<char> contents = t.read();
			Assert::AreEqual(v.size() - 1, contents.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(v[i], contents[i]);
			}
		}
	};

	TEST_CLASS(simpleFileSystem)
	{
	public:

		TEST_METHOD(addValid) // adds two different files to the system, expects success as return value both times
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* txt = sff.createFile("FileName.txt");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreEqual(0, sfs.addFile(txt->getName(), txt));
		}
		TEST_METHOD(addNullFile) // adds a nullptr to the filesystem, expects a non-zero return value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			ImageFile* img = nullptr;
			Assert::AreNotEqual(0, sfs.addFile("FileName.img", img));
		}
		TEST_METHOD(addFileAlreadyExists) // adds the same file twice, the first time should return success, the second time should return a non-zero value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreNotEqual(0, sfs.addFile(img->getName(), img));
		}
		TEST_METHOD(deleteValid) // deletes a valid file (a file that exists and is not open), expects 0 as a return value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreEqual(0, sfs.deleteFile(img->getName()));
		}
		TEST_METHOD(deleteFileDoesNotExist) // deletes a file that has not been added, expects a non-zero return value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreNotEqual(0, sfs.deleteFile(img->getName()));
		}
		TEST_METHOD(openValid) //  opens a valid file that exists and is not already open, expect to see the same file returned
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*res1);
			Assert::IsTrue(sameAddress);
		}
		TEST_METHOD(openFileNotAdded) // opens a file that has not been added, expects a null pointer
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool isNull = res1 == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(openAlreadyOpenedFile) // opens a file twice, the first time should return the same file, the second time should return nullptr
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			AbstractFile* firstOpen = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*firstOpen);
			Assert::IsTrue(sameAddress);
			AbstractFile* secondOpen = sfs.openFile(img->getName());
			bool isNull = secondOpen == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(closeValid) // closes a file that has been added and opened, expect success
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			sfs.addFile(img->getName(), img);
			sfs.openFile(img->getName());
			int res1 = sfs.closeFile(img);
			Assert::AreEqual(0, res1);
		}
		TEST_METHOD(closeNotOpen) // closes a file that has been added but not opened, expects a non-zero return value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreNotEqual(0, sfs.closeFile(img));
		}
		TEST_METHOD(closeNotAdded) // closes a file that has not been added or opened, expects a non-zero return value
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreNotEqual(0, sfs.closeFile(img));
		}
	};

	TEST_CLASS(simpleFileFactory) {
	public:
		TEST_METHOD(createFileValid) // creates two files by calling create on the file factory, the calls should return the new file objects that are both not null
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileFactory sff;
			AbstractFile* res1 = sff.createFile("FileName.img");
			bool isNull1 = res1 == nullptr;
			Assert::IsFalse(isNull1);
			AbstractFile* res2 = sff.createFile("FileName.txt");
			bool isNull2 = res2 == nullptr;
			Assert::IsFalse(isNull2);
		}
		TEST_METHOD(createUnknownExtension) // when a bad extension is passed, the factory should pass back a nullptr
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());

			SimpleFileFactory sfs;
			AbstractFile* res1 = sfs.createFile("FileName.bla");
			bool isNull = res1 == nullptr;
			Assert::IsTrue(isNull);
		}
	};

	// Studio 19 tests
	TEST_CLASS(basicDisplayVisitor) {
	public:
		TEST_METHOD(visitTextFile) { // tests output of basic display visitor for a text file, expects the contents of the file
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			int resWrite = t.write(v);
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			AbstractFileVisitor* bdv = new BasicDisplayVisitor;
			t.accept(bdv);
			string wordShouldBe = "hi";
			string word;
			ss >> word;
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
			Assert::AreEqual(wordShouldBe, word);
			Assert::AreEqual(0, resWrite);
		}
		TEST_METHOD(visitImageFile) { // tests the output the basic display visitor for an image file, expects 5 Xs
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			AbstractFileVisitor* bdv = new BasicDisplayVisitor;
			t.accept(bdv);
			string outputShouldBe = "X";
			string word;
			int count = 0;
			while (ss >> word) { // no skip ws -- wont skip white space! would have to extract one character at a time
				Assert::AreEqual(outputShouldBe, word);
				++count;
			}
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
			Assert::AreEqual(5, count);
		}
	};

	TEST_CLASS(metadataDisplayVisitor) {
	public:
		TEST_METHOD(visitTextFile) { // tests the output of the metadata display visitor for a text file, expects the filename, type and size to be included in the print statement
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
			t.accept(bdv);
			string word;
			std::vector<string> printedWords;
			while (ss >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			std::vector<string>::iterator it2;
			std::vector<string>::iterator it3;
			it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
			bool notEqual2 = it2 == printedWords.end();
			Assert::IsFalse(notEqual2);
			it3 = std::find(printedWords.begin(), printedWords.end(), "text");
			bool notEqual3 = it3 == printedWords.end();
			Assert::IsFalse(notEqual3);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
		}
		TEST_METHOD(visitImageFile) { // tests the output of the metadata display visitor for an image file, expects the filename, type and size to be included in the output
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
			t.accept(bdv);
			string word;
			std::vector<string> printedWords;
			while (ss >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			std::vector<string>::iterator it2;
			std::vector<string>::iterator it3;
			it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
			bool notEqual2 = it2 == printedWords.end();
			Assert::IsFalse(notEqual2);
			it3 = std::find(printedWords.begin(), printedWords.end(), "image");
			bool notEqual3 = it3 == printedWords.end();
			Assert::IsFalse(notEqual3);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
		}
	};
	// Studio 20 tests
	TEST_CLASS(passwordProxy)
	{
	public:

		TEST_METHOD(contstructor) // we expect the name and size of the password proxy to match that of the text file it is assigned with
		{
			// REDIRECT COUT STREAM -- TO PROTECT AGAINST ERRORS
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			unsigned int fileSize = 0;
			// EXPECTATIONS FOR CONSTRUCTION
			Assert::AreEqual(fileName, pp->getName());
			Assert::AreEqual(fileSize, pp->getSize());
			Assert::AreEqual(fileName, realfile->getName());
			Assert::AreEqual(fileSize, realfile->getSize());
		}
		TEST_METHOD(writeValidPassword) // with a valid password, we would expect the size of the pasword proxy and realfile to be updated and return the same value (the size of the vector)
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			ss_in << password;
			// EXPECTATIONS FOR FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(writeInvalidPassword) // if an incorrect password is given, write should not execute and the size of both the password proxy and the real file should remain 0
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			string wrongPassword = "s9K3qL";
			ss_in << wrongPassword;
			// EXPECTATIONS FOR FUNCTION -- INVALID PASSWORD
			Assert::AreNotEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(0), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(0), realfile->getSize());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(appendValidPassword) // we expect that if a good password is given for write and for append, then the proxy and real file should both only have their sizes updated accordingly 
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			unsigned int fileSize = pp->getSize();
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			Assert::AreEqual(0, pp->append(v));
			Assert::AreEqual(static_cast<unsigned int>(fileSize + v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(fileSize + v.size()), realfile->getSize());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(appendInvalidPassword) //  we expect that if a good password is given for write, but an incorrect password is given for append, then the proxy and real file should both only have their sizes updated from the first write
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			unsigned int fileSize = pp->getSize();
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			Assert::AreNotEqual(0, pp->append(v));
			Assert::AreEqual(static_cast<unsigned int>(fileSize), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(fileSize), realfile->getSize());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);

		}
		TEST_METHOD(readValidPassword) // we would expect to see the effects of writing to the proxy with a valid password in the content returned by the read function -- when a valid password is given -- this should also match the read content of the real file
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			// EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
			std::vector<char> contentsPP = pp->read();
			Assert::AreEqual(v.size(), contentsPP.size());
			for (size_t i = 0; i < contentsPP.size(); ++i) {
				Assert::AreEqual(contentsPP[i], v[i]);
			}
			std::vector<char> contentsRF = realfile->read();
			Assert::AreEqual(v.size(), contentsRF.size());
			for (size_t i = 0; i < contentsRF.size(); ++i) {
				Assert::AreEqual(contentsRF[i], v[i]);
			}
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(readInvalidPassword) // when an invalid password is given for the read function, then we would expect the contents vector returned to be empty, however the original file, that does not require a password to read, should be updated from the valid write call
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			std::vector<char> contentsPP = pp->read();
			Assert::AreEqual(static_cast<size_t>(0), contentsPP.size());
			std::vector<char> contentsRF = realfile->read();
			Assert::AreEqual(static_cast<size_t>(v.size()), contentsRF.size());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}

		TEST_METHOD(acceptValidPassword) // we would expect "hi" -- the contents of the file -- to be printed when a valid password is given for accept
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			// EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
			BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
			pp->accept(bdv);
			string wordShouldBe = "hi";
			string word;
			vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
			bool isEqual = it1 == printedWords.end();
			Assert::IsFalse(isEqual);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(acceptInvalidPassword) // we do not expect "hi" (the contents of the file) to be printed when an invalid password is given for accept
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
			// REDIRECT COUT STREAM
			streambuf* backup_out;
			backup_out = cout.rdbuf();
			stringstream ss_out;
			cout.rdbuf(ss_out.rdbuf());
			// REDIRECT CIN STREAM
			streambuf* backup_in;
			backup_in = cin.rdbuf();
			stringstream ss_in;
			cin.rdbuf(ss_in.rdbuf());
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(0, pp->write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), pp->getSize());
			Assert::AreEqual(static_cast<unsigned int>(v.size()), realfile->getSize());
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
			pp->accept(bdv);
			string wordShouldBe = "hi";
			string word;
			vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
			bool isEqual = it1 == printedWords.end();
			Assert::IsTrue(isEqual);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
	};
}