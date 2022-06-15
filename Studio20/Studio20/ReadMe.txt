Studio 20 ReadMe.txt

2. we want to delete the pointer to the actual file 
to avoid dangling pointers

4.
AbstractFile* abf = new TextFile("text");
	AbstractFileVisitor * abd = new BasicDisplayVisitor();
	PasswordProxy p(abf, "pass123");
	
	vector<char> writeIn;
	writeIn.push_back('a');
	writeIn.push_back('b');
	writeIn.push_back('c');
	writeIn.push_back('d');
	writeIn.push_back('e');
	writeIn.push_back('f');
	writeIn.push_back('g');
	writeIn.push_back('h');
	writeIn.push_back('i');
	writeIn.push_back('j');
	
	p.write(writeIn); //input the correct password
	
	p.accept(abd); //input the correct pasword
	p.accept(abd); //input the incorrect password

	writeIn.push_back('k');
	writeIn.push_back('l');
	writeIn.push_back('m');
	p.write(writeIn); //incorrect password
	p.accept(abd);
	
	p.write(writeIn); //correct password
	p.accept(abd);

	return 0;

we wrote and read files to see if they changed when we inputted the correct password