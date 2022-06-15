#include "pch.h"
#include "CppUnitTest.h"
#include "../../SharedCode/TextFile.cpp"
#include "../../SharedCode/ImageFile.cpp"
#include "../../SharedCode/SimpleFileSystem.cpp"
#include "../../SharedCode/SimpleFileFactory.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	// Studio 16 tests
	TEST_CLASS(textFile)
	{
	public:
		TEST_METHOD(contstructor)  // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.txt";
			unsigned int fileSize = 0;
			TextFile t(fileName);
			Assert::AreEqual(fileName, t.getName());
			Assert::AreEqual(fileSize, t.getSize());
		}
		TEST_METHOD(write) // tests write, expects that the function returns success and that the size of the file is updated correctly
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size()), t.getSize());

		}
		TEST_METHOD(append) // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
		{
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
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			int resWrite = t.write(v);
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			t.read();
			string wordShouldBe = "hi";
			string word;
			ss >> word;
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
			Assert::AreEqual(wordShouldBe, word);
			Assert::AreEqual(0, resWrite);
		}
		TEST_METHOD(readWithAppend) // tests that read also works with appending to a file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(0, t.write(v));
			unsigned int fileSize = t.getSize();
			Assert::AreEqual(0, t.append(v));
			Assert::AreEqual(static_cast<unsigned int>(fileSize + v.size()), t.getSize());
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			t.read();
			string wordShouldBe = "hihi";
			string word;
			ss >> word;
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
			Assert::AreEqual(wordShouldBe, word);
		}
	};
	
	// Studio 17 tests
	TEST_CLASS(imageFile)
	{
	public:

		TEST_METHOD(contstructor) // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			Assert::AreEqual(fileName, t.getName());
			Assert::AreEqual(fileSize, t.getSize());
		}
		TEST_METHOD(writeValid) // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			Assert::AreEqual(static_cast<unsigned int>(v.size() - 1), t.getSize());
		}
		TEST_METHOD(writeSizeMismatch) // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '4' };
			Assert::AreNotEqual(0, t.write(v)); // non-zero error returned
			Assert::AreEqual(fileSize, t.getSize()); // contents not added
		}
		TEST_METHOD(writeInvalidPixel) // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert::AreNotEqual(0, t.write(v));
			Assert::AreEqual(fileSize, t.getSize()); // contents not added
		}
		TEST_METHOD(appendInvalid) // tests that append returns a non-zero value (can't append to an image)
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert::AreNotEqual(0, t.append(v)); // can't append to image
		}
		TEST_METHOD(read) // tests that read prints out the contents that are written to the file
		{
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(0, t.write(v));
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			t.read();
			string outputShouldBe = "X";
			string word;
			int count = 0;
			while (ss >> word) {
				Assert::AreEqual(outputShouldBe, word);
				++count;
			}
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
			Assert::AreEqual(5, count);
		}
	};

	TEST_CLASS(simpleFileSystem)
	{
	public:
		TEST_METHOD(addValid) // adds two different files to the system, expects success as return value both times
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			TextFile* txt = new TextFile("FileName.txt");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreEqual(0, sfs.addFile(txt->getName(), txt));
		}
		TEST_METHOD(addNullFile) // adds a nullptr to the filesystem, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = nullptr;
			Assert::AreNotEqual(0, sfs.addFile("FileName.img", img));
		}
		TEST_METHOD(addFileAlreadyExists) // adds the same file twice, the first time should return success, the second time should return a non-zero value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreNotEqual(0, sfs.addFile(img->getName(), img));
		}
		TEST_METHOD(deleteValid) // deletes a valid file (a file that exists and is not open), expects 0 as a return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreEqual(0, sfs.deleteFile(img->getName()));
		}
		TEST_METHOD(deleteFileDoesNotExist) // deletes a file that has not been added, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert::AreNotEqual(0, sfs.deleteFile(img->getName()));
		}
		TEST_METHOD(openValid) //  opens a valid file that exists and is not already open -- checked using add and create methods
		{
			SimpleFileSystem sfs;
			// check using add -- expect to see the same file returned
			AbstractFile* img = new ImageFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*res1);
			Assert::IsTrue(sameAddress);
		}
		TEST_METHOD(openFileNotAdded) // opens a file that has not been added, expects a null pointer
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool isNull = res1 == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(openAlreadyOpenedFile) // opens a file twice, the first time should return the same file, the second time should return nullptr
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
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
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			sfs.addFile(img->getName(), img);
			sfs.openFile(img->getName());
			int res1 = sfs.closeFile(img);
			Assert::AreEqual(0, res1);
		}
		TEST_METHOD(closeNotOpen) // closes a file that has been added but not opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert::AreEqual(0, sfs.addFile(img->getName(), img));
			Assert::AreNotEqual(0, sfs.closeFile(img));
		}
		TEST_METHOD(closeNotAdded) // closes a file that has not been added or opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = new ImageFile("FileName.img");
			Assert::AreNotEqual(0, sfs.closeFile(img));
		}
	};

	// Studio 18 tests
	TEST_CLASS(simpleFileFactory) {
	public:
		TEST_METHOD(createFileValid) // creates two files by calling create on the file factory, the calls should return the new file objects that are both not null
		{
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
			SimpleFileFactory sfs;
			AbstractFile* res1 = sfs.createFile("FileName.bla");
			bool isNull = res1 == nullptr;
			Assert::IsTrue(isNull);
		}
	};
}
