File: README.txt
Assignment: Project #2, Disassembler 
Class: CS530 Fall 2020
Group Members:  Jesus Aviles,   cssc3040, Red ID: 823931557
                Naibi Yilidaer, cssc3054, Red ID: 820217379
                Claire Fiorino, cssc3053, Red ID: 821765822

File Manifest: 
    README.txt
    dis.c
    makefile
    testfiles (Folder):
        sample.obj
        sample.sym
        sample2.obj
        sample2.sym

Compile Instructions:
    In project directory, run "make" command with no arguments

Operating Instructions:
    User should run command: dis <filename>
    (where filename is name of .obj and corresponding .sym file, without file extension)

Design Decisions:
    1. Used arrays of Structures of hold data for symbol table, literal table, each record in obj file,
       and lookup table with mnemonics/formats. 
    2. Utilized helper functions for lookups in the literal, symbol, and mnemonic lookup tables.
    3. Outline of main program:
        a. Parse .sym file (symbol and literal tables)
        b. Parse .obj file
        c. Calculate addressing modes
        d. Print to .lis file
        e. Print to .sic file

Lessons Learned: 
    1. How to read and parse an object file into Instructions
    2. How to effectively store each text instruction and the data associated with it
    3. How to identify and calculate the various SIC/XE addressing modes
    4. How to create a working disassembler for the SIC/XE machine