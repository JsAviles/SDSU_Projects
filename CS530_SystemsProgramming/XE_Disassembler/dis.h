/***************************************************************
*File: dis.h (header file for dis.c) for Project #2
*Class: CS530 Fall 2020
*Group Members:  Jesus Aviles, cssc3040 , Red ID: 823931557
*                Naibi Yilidaer, cssc3054, Red ID:820217379
*                Claire Fiorino, cssc3053, Red ID: 821765822
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef Sym_H
#define Sym_H
struct symtab
{
    char symbol[10];
    char value[7];
    char flag;
};
#endif

#ifndef Lit_H
#define Lit_H
struct literal
{
    char name[15];
    char literal[10];
    int length;
    char address[7]; 
};
#endif

#ifndef Instr_H
#define Instr_H
struct instruction 
{
    char *mnemonic;
    char *symbol;
    int hasSym;
    int opCode;
    int ni;
    int xbpe;
    int ta;
    int format;
    int address;
    int literal;
    int displacement;
    int reserve;
    char * operand;
    int r1;
    int r2;
};
#endif

char *getSymbol(struct symtab symtable[100], int addr);
int getSymboladr(struct symtab symtable[100], char * symbol);
int symContains(struct symtab symtable[100], int addr);
char *getLiteral(struct literal literals[100], int addr);
int getLitaddr(struct literal literals[100], int addr);
int getLitlength(struct literal literals[100], int addr);
int validOpcode(int opcode);
char *getMnemonic(int opcode);
int getFormat(int opcode);
char *getInstrsymbol(struct instruction instrLib [100], int addr);
int main (int argc, char* argv[]);
