Answer studio 16 questions here
1. Jiwoo Seo, Christie Chen, Lina Chang

3 a. Is this an example of “interface inheritance” or “implementation inheritance”?
    interface inheritance because we are not using any implementation from our base class

3 b. Should these member variables be public, protected, or private?
    definitely not public (-"Jon")
    private/protected not super important since we're not extending/inheriting from TextFile

4. Every case ran as expected.
cases include: writing into a text file
               reading it
               appending to it
               writing over it again
			    
5.
setting a pointer to an AbstractFile object to a TextFile object


main : 
	AbstractFile * abFile;
	TextFile text("testing title");

	abFile = & text;
	
	vector<char> writeIn;
	
    
	writeIn.push_back('1');
	
	abFile -> write(writeIn);
	
	cout << "first read" <<endl;

	abFile -> read();

	cout << endl;

	vector<char> appendIn;
	appendIn.push_back('0');
	
	abFile -> append(appendIn);
	abFile -> read();

	abFile -> write(writeIn);
	abFile -> read();

	return 0;
