<h1 align="center">Assignment #1 - Unix Directory Reader </h1>

<div align="center">Operating Systems - Spring 2021</div>

# Table of Contents

1. [About](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#about)
2. [Functionality](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Functionality)
3. [Sample Output](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Sample-output)
4. [Contributors](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Contributors)

## About

The scope of this project was to familiarize ourselves with making system calls, reading the Linux/Unix "Man" pages, and executing programs correctly on systems implementing the POSIX standard via the use of makefiles. This small project allows the user to list out the current working directory or sub directories depending on the user input, please see below for details.

## Functionality

### To get started with compilation and execution on the command line...

* Type **make** as shown below

        $ make

* Then use the executable name **myls**

        $ myls "see Note"
    
* Note - Command line arguments

    1. If no command line arguments are given, the cwd (current working directory) will be listed only showing non-hidden files or directories (see below).
    2. If the optional flag, -h (for hidden), is specified, then the currently directory and all hidden files or directories will also be listed. Note that -h must be specified after the executable name at position argv[1].
    3. One or more command line arguments shall be accepted. Each argument input should name a directory to list.
        * i.e. "myls Pictures Documents" will list the flies in directories "Pictures" followed by the files in "Documents".
        * The cmd line syntax for -h listed above still applies. For example "myls Pictures Documents" with the hidden flag shall be input as --> "myls -h Pictures Documents"
    4. If any specified directories cannot be accessed for any reason, an Error message will appear showing which directory failed to be listed.
    5. The standard output for listing directories is as follows:
        1. Directory name
        2. All file names in the listed directory with one file name per line
        
## Sample output

`$ myls -h dir1 dir2`

![alt text](https://i.gyazo.com/95c85a30dcb346e23d043d93046468f5.png)

## Contributors

* Jesus Sebastian Aviles

    ![alt text](https://i.gyazo.com/30c872a61a8257508866840b44592530.png)

    * sebastian_aviles@yahoo.com

    * [Linkedin](https://www.linkedin.com/in/sebastian-aviles-215b3471/)

* Dao Vo

    * [Linkedin](https://www.linkedin.com/in/dao-vo-07673b1b8/)
