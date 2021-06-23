<h1 align="center">Assignment #3 - Memory Management Unit (Multi-level Paging) </h1>

<div align="center">Operating Systems - Spring 2021</div>

# Table of Contents

1. [About](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#about)
2. [Brigham Young University Trace Distribution Center](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Brigham-Young-University-Trace-Distribution-Center)
3. [Functionality](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Functionality)
4. [Contributors](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A1-UnixDirectoryReader#Contributors)

## About

    This project was created to understand how memory mapping works by simulating multi-level paging. This project helped us gain crucial knowledge and practice implementing pointers on a larger scale. The specification given was to assume a 32 bit logical address space and allow the user to create an N-level page tree. We must also assume an infinite number of frames are available and may ignore page replacement algorithms for the scope of this project.

## Brigham Young University Trace Distribution Center

* The traces (memory references) were collected from a Pentium II running Windows 2000 and are courtesy of the BYU Trace Distribution Center

* byutr.h and byu_tracereader.c are used to read and print the trace files

* trace.sample.tr is a sample of the trace of an executing process and is also the memory reference data used in the page table simulation

## Functionality

### To get started with compilation and execution on the command line...

* Type **make** as shown below

        $ make

* Then use the executable name **pagetable** followed by the path to the byu tracefile, ending with the space separated page sizes

        $ pagetable trace.sample.tr 4 4 8

            • The above will created a 3 level page table with 4 bits for levels 0 and 1, and 8 bits for level 2.
            • Note that any number of pages may be designated but because we are assuming a 32 bit logical address, the page sizes may not exceed a total of 31 bits.
    
* **Optional Arguments (user Interface):**

    1. **-n N**
        
        * Process only the first N amount of memory references
        * Defaults (if not present) to process all memory references contained in the tracefile.

    2. **-o mode**

        * Output "mode", where mode is a string that specifies the desired output
        * Elgible output ***modes***
            * ***bistmasks*** - Display the bitmasking for each level starting with level 0, one bitmask per line
            * ***logical2physical*** - Display the mapping of each logical address to its physical address
            * ***page2frame*** - For each block being used in each level, display the page number followed by the frame number
            * ***offset*** - Display the mapping between the logical addresses and their offsets
            * ***summary*** - Display the summary statistics which include: page size, number of addresses processed, hit and miss rates, bytes required for the pagetable, and the number of frames allocated.
        * If no output mode is selected then the program will default to ***summary***

* Sample output

    `$ pagetable -n 10000 -o summary trace.sample.tr 4 4 8`

    ![alt text](https://i.gyazo.com/f0240665df41870dcbfbd5053e2d678b.png)

## Contributors

* Jesus Sebastian Aviles

    ![alt text](https://i.gyazo.com/30c872a61a8257508866840b44592530.png)

    Contact info:

    * sebastian_aviles@yahoo.com

    * [Linkedin](https://www.linkedin.com/in/sebastian-aviles-215b3471/)

* Dao Vo

    * [Linkedin](https://www.linkedin.com/in/dao-vo-07673b1b8/)
