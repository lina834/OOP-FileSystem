studio 18 answers here

2. 
Implementation of almost all methods (excluding delete and possibly add) are 
implementation dependent based on the SimpleFileSystem, so we'd need to 
alter/rewrite most functionalities

3.
advantages:
encapsulation – releasing responsibility from our main class of knowing
                what file it's created and using
flexibility - we can use polymorphic functions at runtime 
reusable code - some methos don't differ between file systems (such as deletion from memory, etc)


disadvantage:
more complex objects – less code dependencies, but you have more code to worry about


4.

H:\332OOP\Studio18\x64\Debug>Studio18.exe
//Studio18.cpp, output as expected

X X
 X
X X                                             //image file 
1234                                            //text file
12345


5. 
no, only dependent on AbstractFile 

6. 
It works!

H:\332OOP\Studio18\x64\Debug>Studio18.exe
//Studio18.cpp, output as expected

X X
 X
X X                                             //image file 
1234                                            //text file
12345

H:\332OOP\Studio18\x64\Debug>Studio18.exe
//Studio18.cpp, output as expected

X X
 X
X X                                             //image file 
1234                                            //text file
12345

H:\332OOP\Studio18\x64\Debug>Studio18.exe
//Studio18.cpp, output as expected

X X
 X
X X                                             //image file 
1234                                            //text file
12345