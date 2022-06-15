#include "pch.h"
#include "CppUnitTest.h"
#include "../../SharedCode/TextFile.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
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
}
