###########################################################
# File: README for Assignment #1 
# Name: Jesus Sebastian Aviles
# REDID: 823931557
# Edoras Account: cssc3040
# Class: CS530 Fall 2020
###########################################################

Project name    
    • 'xbd'
    • While an official definition for the acronym does not exist, I shall refer to 'xbd' as Hexadecimal Binary Dumper.

Project description
    • xbd is a basic hexadecimal/binary dumper which reads user input, a file to be read and sometimes an option flag (-b),
      and reads the file in its entirety. Based on the user choosing an option, xbd then begins converting each byte into 
      the designated format and prints the address of each row of 16 bytes (hexadecimal) or 6 bytes (binary), the value of 
      each byte, and the character representation of each byte from a range of space to tilde in the ascii chart, replacing
      each unreadable character with a period/dot.
    • This project is meant to emulate the xxd library in linux, only using the input option '-b' or no options, which will
      dump the files bytes in either binary or hexadecimal.

File manifest 
    • xbd.cpp (Source Code)
    • xbd.h (Header file)
    • Makefile (Directives used by "make" to automate compilation of object files)
    • README (Projet Documentation and Instructions)

Compile instructions	
    • This project makes use of the "Make" build automation tool which will automatically build an executable
      from the correct source file(s).
    • Type 'make' in the command line to initaite the compilation process:
        • When 'make' is called from the command line, object files for all source code files will be created
          and combined into a single executable for use.
        • If 'make' has already been called to compile the project, calling 'make' again will attempt to update
          the executable from any source files that have been modified since the last run.
        • If the user wishes to remove compiled source code and any object files created in the process, simply
          use the 'clean' flag (i.e. $ make clean) and all relative files shall be removed from the directory.

Operating instructions (include any/all command line options/arguments, required inputs, etc)
    • Currently there are only two types of acceptable inputs  
        1) Initiating a hexadecimal dump will take a single input, the file in which the user wishes to proceed to dump 
           in hexadecimal format. 
              Example: '$ xbd testfile'
              • The input must be a valid file in the users current working directory.
              • The program will check for validity and existence of a file in the current working directory.
        
        2) Initiating a binary dump will take two inputs, the option which signals the program to proceed into a 
           binary format for dumping and the file which will be converted and dumped into binary format.
              Example: '$ xbd -b testfile'
              • The only acceptible input for the option argument is '-b' for binary mode.
              • The program will not accept any other types of input for the option such as -a, -E, etc...which are 
                available in the Linux version of xxd.

Design decisions
    • One of my main design choices was to handle the output formatting in 2 waves.
        • First was to handle all full rows containing 16 bytes in hexadecimal or 6 byts in binary.
            • This was achieved by taking the amount of bytes read (size) and performing integer division to obtain
              the max number of full rows that could be represented (size/16 for hexadecimal & size/6 for binary) then
              multiplying the division result by either 16 or 6 for hexacedimal or binary which produces the max bytes
              that can be represented in a full row of 16 or 6 bytes.
                Example: ((size/16)*16) for size equal to 923 would produce a 912
                • By using an if statement where i, the variable being incremented for iteration, can not surpass the '912'
                  calculated above, I can be sure that when i reaches 912, it will move onto the "else" statement which 
                  assumes only 1-15 bytes remain and must be formated as the last row.
        • I also used a variable which performed modulo division on the previously mentioned "size" variable which effectively
          held the number of bytes left in the last row.
            • This variable was used in a loop to iterate and print the last row of either chosen format and also to calculate 
              the amount of spaces required for any case of elements left in the last row (1-15).

Description of any extra features/algorithms/functionality you included which were not required
    • There is added error checking empty files, non-existent file, unaccessible files and error in option input.
        • If the user will be prompted with an error message based on the type of error they run into and they must
          try again using correct syntax.
    • I was unsure of how to convert the bytes being read into their respective binary formats from their corresponding
      ASCII values so my approach involved implementing the 'by-hand' arithmetic for converting Decimal integers to 
      Binary. 
        • This was achieved using a nested for loop and a 2d array, an example is shown below:
            for(int i=0; i<size; i++)
            {
                div = dump[i];
                int column=7;
                for(int j=7; j>=0 ;j--)
                {   if(div!=0)
                    {
                        rem = div%2;
                        div = div/2;
                        bdump[i][j] = rem;
                    }
                    else
                    {
                        bdump[i][j] = 0;
                    }
                }
            }
            • Variables:
                div: is the number being divided
                rem: is the remainder which is only ever going to be either 0 or 1
                bdump[row][column]: the 2d array where the row portion not only contains the most significant bit but also 
                                    corresponds to the position of the byte that was read from the file and the column portion
                                    contains the full 8-bit binary representation of the byte.
            • Implementation:
                • Because the calculation in converting decimal to binary calculates starting with the least significant bit, I 
                  designed the insertion of each remainder calculation to be inserted into the bytes corresponding row backwards
                  (Starting from position [row][7] in the 2d array, then [row][6]...[row][0]) effectively masking the byte in the 
                process.
                • The first if statement is in place to check when to stop calculation the binary output, some numbers will require
                  padding zeroes in the most significant bit positions until an 8 bit limit is met.

Deficiencies or bugs
    • In its current state, the project seems to be working as intended, reading in extensionless files and processing
      the dump in the users designated format, hexadecimal or Binary.
    • Upon completion and revision, I see where I could improve my project by making use of more functions to take career
      of the row by row formating, as to eliminate excess length of code.
     
Lessons Learned 
    • This was my first time using C/C++ for a project in my educational career and this project acted as a crash
      course for C++, which I chose to use for this project. Most of my school projects have been in Java and I 
      have alot of experience using printf statements so I felt as though I only had a slight learning curve.
    • I learned about bit masking which was a concept I never came across and was never taught. I also had to 
      be creative and create my own general formula for prediction the exact amount of spacing in the last row of
      print in order to obtain a consistent format output for a last row which contained any amount of bytes.
    • This was my first time learning how to use and implementing a Makefile which I now realize is a great tool
      for projects which consist of a large amount of source/object files which require compilation.
        • Learning how to create a makefile consisted of reading about the make library, watching tutorials on 
          the required syntax, and ofcourse a little bit of trial and error.
    • Lastly, I learned about the xxd library in linux and its uses in "mail-safe" data transfer, data recovery,
      reverse engineering, and programming in general.