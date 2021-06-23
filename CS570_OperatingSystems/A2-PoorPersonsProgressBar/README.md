<h1 align="center">Assignment #2 - Poor Person's Progress bar </h1>

<div align="center">Operating Systems - Spring 2021</div>

# Table of Contents

1. [About](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A2-PoorPersonsProgressBar#about)
2. [Functionality](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A2-PoorPersonsProgressBar#Functionality)
3. [Contributors](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A2-PoorPersonsProgressBar#Contributors)

## About

    The scope of this project is to gain experience working with POSIX threads. Using multiple threads, the script shall accept a file as input on the command line, count how many words and bytes are in the file while simultaneously printing out '+' or '-' to simulate a progress bar loading which is tracking the % of the file being read in real time. Once the progress bar thread completes its assigned task, the output will then display how many words the input file contains.

## Functionality

### To get started with compilation and execution on the command line...

* Type **make** as shown below

        $ make

* Then use the executable name **wordcount** followed by the **file** to be read.

        $ wordcount "inputfile.txt"
    
* Command line arguments

    1. Only a single file will be accepted as input.
    2. Error handling for various cases implented:
        * Multiple input files
        * Incorrect spelling
        * File not found or inacessible

* Sample output

    `$ wordcount test2.txt`

    ![alt text](https://i.gyazo.com/4aa6ff835d74c6f9bd142ae816f0a41c.png)

## Contributors

* Jesus Sebastian Aviles

    ![alt text](https://i.gyazo.com/30c872a61a8257508866840b44592530.png)

    Contact info:

    * sebastian_aviles@yahoo.com

    * [Linkedin](https://www.linkedin.com/in/sebastian-aviles-215b3471/)

* Dao Vo

    * [Linkedin](https://www.linkedin.com/in/dao-vo-07673b1b8/)
