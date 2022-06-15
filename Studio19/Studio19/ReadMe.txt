studio 19 answers here

2. 
code:
	AbstractFileSystem* sysPtr = new SimpleFileSystem();
	AbstractFileFactory* facPtr = new SimpleFileFactory();
	

	sysPtr->addFile("test2.txt", facPtr->createFile("test2.txt"));
	AbstractFile* text = sysPtr->openFile("test2.txt");
	vector<char> writeIn2;
	writeIn2.push_back('1');
	writeIn2.push_back('2');
	writeIn2.push_back('3');
	writeIn2.push_back('4');

	text->write(writeIn2);
	text->read();
	vector<char> vec = text->read();

	for(size_t i = 0; i < vec.size(); ++i){
		cout << vec[i];
	}

	cout << endl;
	cout << endl;
	writeIn2.push_back('5');
	text->write(writeIn2);
	text->read();

	vec = text->read();

	for(size_t i = 0; i < vec.size(); ++i){
		cout << vec[i];
	}
	cout << endl;
	return 0;

description:
    we created a file and inputted a vector<char>, used a local 
    variable to save the vector returned by read() and printed it.
    Then, we added to the vector and then printed it to see the change.


3.
    (for textfile first)
    1. call accept on a polymorphically bound object				 // objectStruture -> ConcreteElement (text file)
        accept called on an AbstractFile * af						
    2. the object calls visit on the visitor class, which		 	// ConcreteElement (text file) -> concreteVisitor
        visit_<> (in visitor) based on what af is at runtime		// 1st step in double dispatch
    3. visitor calls the implementation for TextFile * tf			// 2nd step
        implementation (in concrete element) based on what tf is at runtime
    4. repeats #1 for image file
    5. repeats #2 for image file
    6. repeats #3 for image file

4.
    Each object doesn't need to know how it's printed