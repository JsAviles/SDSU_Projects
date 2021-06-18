/*************************************************************************************
* Name:        	Jesus Aviles, cssc3040, RED ID: 823931557
				Dao Vo      , cssc3020, RED ID: 820901504
* Class:        CS530, Fall 2020 
* Assignment:   Project 3
* File:        	Parser.h
* Description:  header file for Parser.cpp
*************************************************************************************/
#ifndef parsy
#define parsy

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstring>

using namespace std;


void parseFile(char *file);
vector <char*> vArray[50];
char * evaluation [50];

	//Add a third array to save which rule failed "token/op/exp/etc.."
void verify(int size);
char *valid(char *tempV, int size);


/*
BNF Grammer
what we need
------------
identify op
	op ::= +|-|/|*|%
	
identify <char>
	::= a|b|c|d|e|f|g|...|X|Y|Z **use ascii to define range
	
identify digit
	<digit> ::= 0|1|2|3|4|5|6|7|8|9
	
identify id
	<id> ::= <char>|<id><char>|<id><digit>
	
identify expression
	id op id {op id} **any length as long as pairs of op and id are added
	
identify assignment
	id = exp;

check if proper op
check if proper statement
check if proper id (cant start with number, only first input must be a char)
check if proper integer
continued...
*/

#endif

