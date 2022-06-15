

commenting: 

***** when done, put ----- ****

------- catds parsing strat h 
------- catds parsing strat cpp
------- abstract command h
------- abstract file h
------- abst file fac h
------- abst file system h
------- abst file visitor 
------ abst parsing strategy h
------- basic display visitor cpp
------- basic disply visitor h
------- cat command cpp
------- cat command h 
-------commnd prompt cpp        
-------command prompt h         
------- command test h
------- command test cpp
------- copy command cpp
------- copy command h
------- display command h
------- display command cpp
------- image file cpp
------- image file h
------- ls command h
------- ls command cpp
-------macrocommand cpp
------- macrocommand h
-------MetadataDisplay visitor cpp
-------MetadataDisplay visitor h
------- rename parsing strat cpp
------- rename parsing strat h
-------simplefilefac cpp
-------simplefilefac h
------- simple file system h
------- simple file system cpp
------- textfile cpp
------- textfile h
------- touch command cpp
------- touch command h
------- remove command cpp
------- remove command h
------- password proxy cpp
------- password proxy h

#########################################################
Author: Christie Chen, christiec@wustl.edu
        Lina Chang, n.chang@wustl.edu
        Jiwoo Seo, jiwooseo@wustl.edu

Work Distribution
        1. ls		- all together
        2. rm 		- JIWOO 
        3. password - CHRISTIE 
        4. cat  	- CHRISTIE 
        5. ds       - JIWOO 
        6. copy 	- JIWOO 
        7. macro    - LINA 
        8. rn       - LINA 
        10. extra credit - CHRISTIE

Additional information
     Because we have a second Macrocommand as our extra credit, we added an info() method in 
          AbstractParsingStrategy in order to correctly display the information about each command.
     Internal return values can be found consolidated in AbstractFile.h and are specified as follows:
              	0    success - used for general successful execution
               1    file_not_found - the file specified is not in the file system
               2    null_file - tried to add a null file to the file system
               3    file_already_exists - tried to add a duplicate file to the file system
               4    file_is_open - tried to delete an open file from the system
               5    file_not_open - tried to close a file that was not open
               6    command_error - a command has returned an error level that is not success               
               7    file_not_created - unable to create a file was created
               8    file_not_added - unable to add the file to the file system
               9    input_line_error - issue with the input passed to the command line for the cat command
               10   file_dne - tried to use a command on an invalid file 
               11   unable_to_copy - could not copy file
               12   arg_error - issue with the input passed to the command line for the copy command
               13   can_not_write - can not write to the file
               14   wrongPassword - incorrect password 
               15   unable_to_rm - can not remove file
               16   file_not_supported - can not append to this type of file
               
     Return values for the program are found in CommandPrompt.h and are as follows:
               0    success - general successful execution
               1    quit - used when the user quits the program
     Please note, the executable builds in either the Lab5\x64\Debug folder OR the Lab5\Debug folder.
        To avoid running an old build of the program, please check the build location in the output.
        Our final build is located at Lab5\x64\Debug\Lab5.exe 
1. TESTS 
 ** deleted command prompt lines (see below) for the readability. 
 ** Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
                
        1) touch - creating files
                $   touch text.txt
                $   touch image.img
                $   ls
                image.img                text.txt


        2) rm - deleting files
                $   ls
                image.img                text.txt
                $   rm image.img
                $   ls
                text.txt


        3) ls - list of the files
                $   ls
                image.img                text.txt
                $   ls -m
                image.img                image     0
                text.txt                 text      0
                $   cat text.txt
                text.txt
                Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
                1234
                :wq
                >> Writing to file. Please enter password if applicable. <<
                $   ls -m
                image.img                image     0
                text.txt                 text      4

           // ls -m displays a single file per line aling with the metadata associated with that file. 
           // The behavior is correct


        3) cat , ds - cat: write/append, ds: display

           // text files
                $   cat text.txt
                text.txt
                Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
                12345
                :wq
                >> Writing to file. Please enter password if applicable. <<
                $   cat text.txt -a
                text.txt
                File contents:
                12345
                Enter data you'd like to append to the file. Enter ":wq" to save and exit, enter ":q" to exit without saving.
                6789
                :wq
                >> Appending to file. Please enter password if applicable. <<
                $   ds text.txt
                123456789
                
           // image files
                $   touch image.img
                $   cat image.img
                image.img
                Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
                X X X X X3
                :wq
                >> Writing to file. Please enter password if applicable. <<
                $   ds image.img
                X X
                 X
                X X
                $   ds image.img -d
                X X X X X

            // cat with no save ":q"
               $   ds text.txt
               first text here
               Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
               $   cat text.txt
               text.txt
               Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
               new text, not added
               :q
               Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
               $   ds text.txt
               first text here

           // As shown above, cat <filename> writes to the file, and cat <filename> -a appends to the file.
           // ds <filename> displays contents in format, and ds <filename> -d displays contents in an unformatted way.
           // The behavior is correct.

          

        4) copy - copy a file into the file system
                $   ls
                text.txt
                $   ds text.txt
                123456789
                $   cp text.txt copiedFile
                $   ls
                copiedFile.txt           text.txt
                $   ds copiedFile.txt
                123456789
                $   cat copiedFile.txt
                copiedFile.txt
                Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
                new text
                :wq
                >> Writing to file. Please enter password if applicable. <<
                $   ds text.txt
                123456789

           // Contents of the file is also copied into the new file. 
           // the copy is a unique file. writing to the copy does not change the original.
           // The behavior is correct.


        5) rn - renaming the file
                $   ls
                copiedFile.txt           text.txt
                $   rn text.txt renamed
                $   ls
                copiedFile.txt           renamed.txt
                $   ds renamed.txt
                123456789 

           // text.txt is renamed to renamed.txt 
           // the contents are preserved. 
           // The behavior is correct.
        

        6) password proxy - behaviors of password protected files.

           // touch <filename> -p creates a password protected file.
           // users are prompted to enter the password.
                $   touch password.txt -p
                What is the password?
                123

           // when writing/appending or displaying the password protected files,
           //      users are prompted to enter the password.
                $   cat password.txt
                password.txt
                Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
                hello, world
                :wq
                >> Writing to file. Please enter password if applicable. <<
                Password:
                123
                $   ds password.txt
                Password:
                123
                hello, world

           // copying a password protected files.
           // password is also copied
                $   cp password.txt copy
                $   ls
                copy.txt                 password.txt
                $   ds copy.txt
                Password:
                123
                hello, world


        7) command prompt

           // when the user enters 'help', the list of commands are presented.
                $   help
                cat
                catds
                cp
                ds
                ls
                rm
                rn
                touch

           // when the user enters 'help <command name>', the information of the command is presented.
                $   help ds
                ds opens a file and displays its contents in format
                ds -a opens a file and displays its data only
                Usage:  ds <filename>  or  ds <filename> -d

           // when the user enters q, it quits the program.
           // the errorlevel is 0, which indicates the success.
           // the behavior is correct.
                Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
                $   q

                H:\332OOP\Lab5\x64\Debug>echo %errorlevel%
                0

            

2. errors/bug we encountered
        syntax issues (a lot of syntax issues...)
        Some circular dependecy/inheritance errors
        We didn't have as many compiler errors/bugs, but there were minor logic issues that caused the program
                to run incorrectly.




3. extra credit 

     // catds was created using a Macrocommand in the same way as rename. Implementation 
     // found in CatDSParsingStrategy.h and CatDSParsingStrategy.cpp. 

     1) catds on regular files
          $   touch file.txt
          $   catds file.txt
          file.txt
          Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
          hello, world
          :wq
          >> Writing to file. Please enter password if applicable. <<
          hello, world

          $   touch image.img
          $   catds image.img
          image.img
          Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
          X X X X X3
          :wq
          >> Writing to file. Please enter password if applicable. <<
          X X
           X
          X X
     2) catds on password protected files
          $   touch filePass.txt -p
          What is the password?
          123
          Enter a command, q to quit, help for a list of commands, or help followed by a command name for more information about that command.
          $   catds filePass.txt
          filePass.txt
          Enter data you'd like to write to the file. Enter ":wq" to save the file and exit, enter ":q" to exit without saving.
          hello, passworded file
          :wq
          >> Writing to file. Please enter password if applicable. <<
          Password:
          123
          Password:
          123
          hello, passworded file








