##################################################
#Name:        	Jesus Aviles, cssc3040 ,823931557#
#		Dao Vo, cssc3020, 820901504      #
#Class:        	CS530, Fall 2020                 #
#Assignment:    Project 3                        #
##################################################

---------------
  Descripton
---------------
This parser project is written in C++ and it shall take statements from a 
text file and output the validity of their statements into an output text
file named parsed.txt. The purpose of this project to is demonstrate the 
working and how grammar is evaluated such as it would within many programming 
languages. The grammatical structure of this project is based on Backus-Naur 
form(BNF). Below are the grammars used within this project.

GRAMMER
-------
operator
	op ::= +|-|/|*|%
	
character
	<char> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|
		A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|Q|X|Y|Z
	
digit
	<digit> ::= 0|1|2|3|4|5|6|7|8|9
	
identifier
	<id> ::= <char>|<id><char>|<id><digit>
	
integer
	<int> ::= <digit>|<int><digit>
	
expression
	id op id {op int|id} | id op int {op int|id}
	
assignment
	id = exp ;

---------------
    Files
---------------
README, makefile, Parser.h, Parser.cpp, statements.txt, test1.txt, test2.txt

makefile:
	This file will be used to build the program which will be executed.
	Instuctions to do so will be further elaborated later within this README.
	- Invoke make with "$ make" commands
	- "$ make clean" : removes source code executable and specified txt files
Parser.cpp:
	This is the driver class that also contains the definitions of the methods that are
	declared within Parser.h. This class is able to check the arguements from the 
	command line to read in a file that is to be evaluated or it will use search for 
	"statements.txt" to evaluate. This file will then read and store each statements into
	appropriate vectors to evaluate if the proper grammers are being used and will output
	to the user the statements are valid or invalid. 
Parser.h:
	This header file contains variables and functions used within the Parser.cpp such as
	vector char* to hold values of the statements that are read in as well as functions
	to test the validity of the grammers that are in use.
statements.txt:
	This is a test file that was used during our trials. It was provided by Guy Leonard 
	with additional statements added for our testings.
test1.txt/test2.txt
	Modified test files to ensure evaluation of grammar was consistent

---------------	
   Compile
---------------
First build the program by running the 'make' command in the terminal which will produce
an executable named 'parser'. 
Conversely, you can remove the build with the command, 'make clean.'

Compile on edoras:
	To comiple on edoras, simply invoke with '$ make'

	To execute the program by calling 'parser' which will evaluate a folder named statements.txt by
	default or a custom text file name following the executable.
	EXAMPLE:
		'$ parser'
	OR
		'$ parser <filename>'

	The results of the evaluated statements will be inserted into a new text file named parsed.txt and
	the contents are visible by using the command:
		'$ cat -v parsed.txt'
			OR
		'$ vi parsed.txt'
			OR
		'$ vim parsed.txt'
		
	In addition, for the cleaner output by removing '^M' within the file, please use the command:
		'$ sed -e "s/\r//g" parsed.txt > sedparsed.txt'

Compile on Windows
	To execute on the program, if you have MINGW installed you can use your terminal such as 'Git bash'
	to call make or use g++ <Parser.cpp> -o parser, then call the executable with the syntax:

	'./parser' OR './parser <filename>', as previously stated, if called with no input, parser will default 
	to 'parser statements.txt' or the user may specify which file they would like to be read.

---------------
Bugs and Error
---------------
Outdated software on edoras
	Code was originally compiled and tested on our local machines using our preferred IDE's and txt editors.
	We had issues when transferring our code into edoras which affected the parsed.txt output file. Within the
	file contain '^M' which would impede output when calling the 'cat' command. The way we worked around this 
	was when we used the flag '-v' when calling 'cat' which fixed the formatting. The final way it was dealt with 
	was when using 'sed' command which was defined within this README's compile instruction which removed the ^M
	(control m - newline)errors and allows the user to view the txt file without any flag calls.
	

---------------
Lessons Learned
---------------
	1. C++ can become very unhappy with improper memory allocation.
	2. It is important to null terminate char *'s when working with C Strings.
	3. Evaluate grammar using BNF form
	4. Lexical Analysis
	5. the g++/gcc red hat distribution is very old on edoras
 
 