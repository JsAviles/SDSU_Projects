/***************************************************************
* File: dis.c (source code file) for Project #2
* Class: CS530 Fall 2020
* Group Members:  Jesus Aviles,   cssc3040, Red ID: 823931557
*                 Naibi Yilidaer, cssc3054, Red ID: 820217379
*                 Claire Fiorino, cssc3053, Red ID: 821765822
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dis.h"

//*********************************************************
//lookup table struct and corresponding get functions
//*********************************************************
const int LtableSize = 59;
 
struct instructNode
{
    int   opCode;
    char  *operation;
    int  format;    
};

// format 3 includes format 4
const struct instructNode Ltable [] = {
    {0x00, "LDA", 3},   {0x04, "LDX", 3},    {0x08, "LDL", 3},    {0x0C, "STA", 3},
    {0x10, "STX", 3},   {0x14, "STL", 3},    {0x18, "ADD", 3},    {0x1C, "SUB", 3},
    {0x20, "MUL", 3},   {0x24, "DIV", 3},    {0x28, "COMP", 3},   {0x2C, "TIX", 3},
    {0x30, "JEQ", 3},   {0x34, "JGT", 3},    {0x38, "JLT", 3},    {0x3C, "J", 3},
    {0x40, "AND", 3},   {0x44, "OR", 3},     {0x48, "JSUB", 3},   {0x4C, "RSUB", 3},
    {0x50,"LDCH", 3},   {0x54, "STCH", 3},   {0x58, "ADDF", 3},   {0x5C, "SUBF", 3},
    {0x60, "MULF", 3},  {0x64, "DIVF", 3},   {0x68, "LDB", 3},    {0x6C, "LDS", 3},
    {0x70, "LDF", 3},   {0x74, "LDT", 3},    {0x78, "STB", 3},    {0x7C, "STS", 3},
    {0x80, "STF", 3},   {0x84, "STT", 3},    {0x88, "COMPF", 3},
    {0x90, "ADDR", 2},  {0x94, "SUBR", 2},   {0x98, "MULR", 2},   {0x9C, "DIVR", 2},
    {0xA0,"COMPR", 2},  {0xA4, "SHIFTL", 2}, {0xA8, "SHIFTR", 2}, {0xAC, "RMO", 2},
    {0xB0, "SVC", 2},   {0xB4, "CLEAR", 2},  {0xB8, "TIXR", 2},
    {0xC0, "FLOAT", 1}, {0xC4, "FIX", 1},    {0xC8, "NORM", 1},
    {0xD0, "LPS", 3},   {0xD4, "STI", 3},    {0xD8, "RD", 3},     {0xDC, "WD", 3},
    {0xE0, "TD", 3},    {0xE8, "STSW", 3},   {0xEC, "SSK", 3},
    {0xF0, "SIO", 1},   {0xF4, "HIO", 1},    {0xF8,"TIO", 1}
};


//*********************************************************
//retrieve the symbol at the given address
//*********************************************************
char *getSymbol(struct symtab symtable[100], int addr)
{
    int i=0;
    char * temp;
    while(symtable[i].value != NULL)
    {
        if((int)strtol(symtable[i].value, NULL, 16) == addr)
        {
            temp = symtable[i].symbol;
            return temp;
        }
        else
        {
            i++;
        }
    }
    return NULL;
}

//*********************************************************
//retreive the address for the given symbol
//*********************************************************
int getSymboladr(struct symtab symtable[100], char * symbol)
{
    int i=0;
    int temp;
    while(symtable[i].value != NULL)
    {
        if(symtable[i].symbol == symbol)
        {
            temp = (int)strtol(symtable[i].value, NULL, 16);
            return temp;
        }
        else
        {
            i++;
        }
    }
    return 99999;
}

//*********************************************************************
//check to see if the symtable contains a symbol at the given address
//*********************************************************************
int symContains(struct symtab symtable[100], int addr)
{
	int i=0;
    while(symtable[i].value != NULL)
    {
        if((int)strtol(symtable[i].value, NULL, 16) == addr)
        {

            return 1;
        }
        else
        {
            i++;
        }
    }
    return 0;
}

//*********************************************************
//return Literal Name declaration
//*********************************************************
char *getLiteral(struct literal literals[100], int addr)
{
    int i=0;
    while(literals[i].address[0] != '\0')
    {
        if((int)strtol(literals[i].address, NULL, 16) == addr)
        {
            return literals[i].literal;
        }
        else
        {
            i++;
        }
    }
    return NULL;
}

//*********************************************************
//return Literal Address
//*********************************************************
int getLitaddr(struct literal literals[100], int addr)
{
	int i=0;
    while(literals[i].address[0] != '\0')
    {
        if((int)strtol(literals[i].address, NULL, 16) == addr)
        {
            return (int)strtol(literals[i].address, NULL, 16);
        }
        else
        {
            i++;
        }
        
    }
    //address not found in literal table, return absurd number meant to represent a flag
    return 999999;
}

//*********************************************************
//get length of literal
//*********************************************************
int getLitlength(struct literal literals[100], int addr)
{
	int i=0;
    while(literals[i].address[0] != '\0')
    {
        if((int)strtol(literals[i].address, NULL, 16) == addr)
        {
            return literals[i].length;
        }
        else
        {
            i++;
        }
    }
    return 0;
}

//*********************************************************
//Check to see whether the opcode exists
//*********************************************************
int validOpcode(int opcode)
{
    int l = 0; int r =LtableSize;
        while (l<=r)
        {
            int m = (l+r)/2;
            if (Ltable[m].opCode == opcode)
                return 1;
            if (Ltable[m].opCode > opcode)
                r = m-1;
            else
                l = m+1;
        }
        return 0;
}
//*********************************************************
//return the instruction mnemonic for the given opcode
//*********************************************************
char *getMnemonic(int opcode)
{
    int l = 0; int r =LtableSize;
        while (l<=r)
        {
            int m = (l+r)/2;
            if (Ltable[m].opCode == opcode)
                return Ltable[m].operation;
            if (Ltable[m].opCode > opcode)
                r = m-1;
            else
                l = m+1;
        }
        return NULL;
}

//*********************************************************
//return the format for a given opcode
//*********************************************************
int getFormat(int opcode)
{ 
    int l = 0; int r =LtableSize;
        while (l<=r)
        {
            int m = (l+r)/2;
            if (Ltable[m].opCode == opcode)
                return Ltable[m].format;
            if (Ltable[m].opCode > opcode)
                r = m-1;
            else
                l = m+1;
        }
        return 99999;
}


//***************************************************************************
//Takes an address and returns the symbol at said address...if it exists
//***************************************************************************
char *getInstrsymbol(struct instruction instrLib [100], int addr)
{
    int i=0;
    char * temp;

    while(instrLib[i].address != '\0')
    {
        if(instrLib[i].address == addr)
        {
            temp = instrLib[i].symbol;
            return temp;
        }
        else
        {
            i++;
        }
    }
    return NULL;
}

/**********************************************************/
/*                         MAIN                           */
/**********************************************************/
int main (int argc, char* argv[]) 
{
    struct instruction instrLib [100];
    char c;
    int FC = 252;
    int tempOP;
    int tempNI;
    int tempXBPE;
    int tempTA;
    int tempFormat;
    int startAdr;
    int endAdr;
    int firstExec;
    int tempAdr;
    int tempR1;
    int tempR2;
    int modRec[25];
    int addressCtr = 0;
    int lastInstr;
    char litValue[6];
    char startAdrAR [6];
    char endAdrAR [6];
    char firstInstr [6];
    char opTemp [2];
    char taTempA [5];
    char taTempB [3];
    char tempModR [6];
    int i;
    int X;
    int BASE;
    int litFlag = 0;
    struct symtab symtable [100];
    struct literal literals [100];

//***************************************************************************
//filename strings to open up .obj/.sym files in current working directory
//***************************************************************************
    char symfilename [12];
    char objfilename [12];
    int strLength = strlen(argv[1]);
    int fctr = 0;

    //set symtab file name
    for(i=0; i< strLength;i++)
    {   
        symfilename[i] = argv[1][i];
        fctr++;
    }
    symfilename[fctr] = '.';
    fctr++;
    symfilename[fctr] = 's';
    fctr++;
    symfilename[fctr] = 'y';
    fctr++;
    symfilename[fctr] = 'm';
    fctr++;
    symfilename[fctr] = '\0';
    fctr = 0;

    //set objfilename
    for(i=0; i< strLength;i++)
    {   
        objfilename[i] = argv[1][i];
        fctr++;
    }
    objfilename[fctr] = '.';
    fctr++;
    objfilename[fctr] = 'o';
    fctr++;
    objfilename[fctr] = 'b';
    fctr++;
    objfilename[fctr] = 'j';
    fctr++;
    objfilename[fctr] = '\0';
    fctr = 0;

//**********************************************************
//Parse symtab and create symtable
//**********************************************************

    FILE *symtabfile;
    symtabfile = fopen(symfilename, "r");

    //Which line in the text file we are reading 
    int linectr = 0;
    
    //Which row in symbol/literal table we are reading- also determines index in 
    //array of structs
    int symCount = -1;
    int litCount = -1;
    
    //Which field we are currently reading (ex. address, name, etc.)
    int fieldcount = 0;
    
    //Index of char in each field string- will be reset to zero each time we move to a new field
    int strindex = 0;
    
    if (symtabfile == NULL) 
    {
        printf("Error: .sym file does not exist or may not be accessible.\n");

    }
    else 
    {
        //READ SYMBOL TABLE
        while ((c = fgetc(symtabfile)) != EOF){
            //Increment line count if new line reached
            if (c == '\n'){
                //If end of symtab reached (2 newlines in a row), break
                if ((c = fgetc(symtabfile)) == '\n'){
                    break;
                }
                else {
                    ungetc(c, symtabfile);
                }
                linectr += 1;
                if (linectr >= 2) {
                    symCount += 1;
                }
                continue;
            }
            //If reader is past the table header
            if (linectr >= 2) {
                //If there is white space
                if (c == ' ') {
                    while (c == ' ') {
                        c = fgetc(symtabfile);
                    }
                    c = ungetc(c, symtabfile);
                    //Null terminate each field if necessary
                    if (fieldcount == 0){
                        symtable[symCount-1].symbol[strindex+1] = '\0';
                    }
                    if (fieldcount == 1){
                        symtable[symCount-1].value[strindex] = '\0';
                    }
                    fieldcount += 1;
                    strindex = 0;
                    continue;
                }
                //Add data to struct depending on which field it is
                else if (fieldcount == 0){
                    symtable[symCount].symbol[strindex] = c;
                    strindex += 1;
                }
                else if (fieldcount == 1){
                    symtable[symCount].value[strindex] = c;
                    strindex +=1;
                }
                else if (fieldcount == 2){
                    symtable[symCount].flag = c;
		            fieldcount = 0;
                    strindex = 0;
                }
	        }
        } 
    //}
    
        //Reinitialize variables to zero
        linectr = 0;
        fieldcount = 0;
        strindex = 0;
    
//**************************
//Read literal table
//**************************
        while ((c = fgetc(symtabfile)) != EOF){
            //Increment line count if new line reached
            if (c == '\n'){
                //If end of symtab reached (2 newlines in a row), break
                if ((c = fgetc(symtabfile)) == '\n'){
                    break;
                }
                else {
                    ungetc(c, symtabfile);
                }
                linectr += 1;
                if (linectr >= 2) {
                    litCount += 1;
                }
                continue;
            }
            //If reader is past the table header
            if (linectr >= 2) {
                //If there is white space
                if (c == ' ') {
                    while (c == ' ') {
                        c = fgetc(symtabfile);
                    }
                    c = ungetc(c, symtabfile);
                    //Null terminate each field if necessary
                    if (fieldcount == 0){
                        literals[litCount-1].name[strindex] = '\0';
                    }
                    if (fieldcount == 1){
                        literals[litCount-1].literal[strindex] = '\0';
                    }
                    if (fieldcount == 3){
                        literals[litCount-1].address[strindex] = '\0';
                        fieldcount = 0;
                    }
                    fieldcount += 1;
                    strindex = 0;
                    continue;
                }
                //Add data to struct depending on which field it is
                else if (fieldcount == 0){
                    literals[litCount].name[strindex] = c;
                    strindex += 1;
                }
                else if (fieldcount == 1){
                    literals[litCount].literal[strindex] = c;
                    strindex +=1;
                }
                else if (fieldcount == 2){
                    literals[litCount].length = c-'0'; // - char 0 to get int value of character
                    strindex = 0;
                }
                else if (fieldcount == 3){
                    literals[litCount].address[strindex] = c;
                    strindex += 1;
                }
                
            //Null terminate final address field in struct
            literals[litCount].address[6] = '\0';
            }
        }//End of symtab parse
        fclose(symtabfile);
    }

//**********************************************************
//Symtab has been parsed, now parse the .obj file
//**********************************************************
    FILE *objFile;
    objFile = fopen(objfilename, "r");

    int charCtr;
    int opLength;
    int instrCtr = 0;
    int modCtr = 0;
    int flag = 0;
    char progName[6];
    int valCtr;

    //Error check for whether or not the designated file is accessible or present
    if (objFile == NULL)
    {
        printf("Error: .obj file does not exist or may not be accessible.\n");
        return 0;
    }
    else
    {
        while ((c = fgetc(objFile)) != EOF)
        {
            charCtr = 0;
            if(c == 'H')
            {
                int h;
                //read the Header record line
                for(h=0; h<19;h++)
                {
                    if( h < 7 )
                    {
                        c = fgetc(objFile);
                        progName[h] = c;
                    }
                    //save starting address
                    else if(h >= 7 && h <13)
                    {
                        startAdrAR[h -7] = c;
                        c = fgetc(objFile);

                    }
                    //save ending address
                    else if (h >= 13 && h < 19)
                    {
                        endAdrAR[h - 13] = c;
                        c = fgetc(objFile);
                    }
                }
                progName[6] = '\0';
                startAdrAR[6] = '\0';
                startAdr = (int) strtol(startAdrAR, NULL, 16);
                endAdrAR[6] = '\0';
                endAdr = (int) strtol(endAdrAR, NULL, 16);

                struct instruction tempInstr;
                tempInstr.address = startAdr;
                tempInstr.mnemonic = "START";
                tempInstr.symbol = progName;
                tempInstr.operand = startAdrAR;
                tempInstr.hasSym = 1;
                tempInstr.format = 5;
                instrLib[instrCtr] = tempInstr;
                instrCtr++;
            }
            if(c == 'T')
            {
                //parse to col 8-9 (length of object code)
                for(i = 0; i<7; i++)
                {
                    c = fgetc(objFile);
                }
                //take columns 8-9 and set int ctr to the length in Decimal
                for(i=0; i<2; i++)
                {
                    opTemp[i] = c;
                    c = fgetc(objFile);
                }
                opTemp[2] = '\0';
                opLength = (int) strtol(opTemp, NULL, 16);
                while(charCtr < (opLength*2))
                {
                    //check the Littab struct to see if there is supposed to be a literal at the current address
                    while((getLitaddr(literals,((charCtr/2) + startAdr)))!=999999)
                    {
                        valCtr = 0;
                        struct instruction tempInstr;
                        tempInstr.format = 0;
                        tempInstr.address = getLitaddr(literals,((charCtr/2) + startAdr));
                        tempInstr.operand = getLiteral(literals,((charCtr/2) + startAdr));
                        tempInstr.mnemonic = "*";

                        //check the next byte for information
                        for(i=0; i< getLitlength(literals,(charCtr/2) + startAdr);i++)
                        {
                            litValue[i] = c;
                            c = fgetc(objFile);
                            valCtr++;
                            charCtr++;
                        }
                        litValue[valCtr] = '\0';
                        tempInstr.literal = ((int)strtol(litValue, NULL, 16));
                        instrLib[instrCtr] = tempInstr;
                        instrLib[instrCtr-1].operand = instrLib[instrCtr].operand;
                        instrCtr++;
                        addressCtr += 1;
                        litFlag = 1;
                    }
                    //check next byte (next 2 chars) and calc/set the opCode of the instruction
                    for(i=0; i<2; i++)
                    {
                        opTemp[i] = c;
                        c = fgetc(objFile);
                        charCtr++;
                    }
                    opTemp[2]='\0'; 
                    //check opcodes for formats 1/2
                    tempOP = ((int)strtol(opTemp, NULL, 16));

                    //if the 8bit opcode exists then go into format 1/2 instruction loops
                    if(validOpcode(tempOP) == 1)
                    {
                        if(getFormat(tempOP) == 1)
                        {
                            struct instruction tempInstr;
                            tempInstr.address = addressCtr;
                            tempInstr.opCode = tempOP;
                            tempInstr.format = 1;
                            tempInstr.ta = tempTA;
                            tempInstr.hasSym = 0;
                            instrLib[instrCtr] = tempInstr;
                            instrCtr++;
                            addressCtr += tempInstr.format;
                        }
                        if(getFormat(tempOP) == 2)
                        {
                            //get next byte for the operand value
                            for(i=0; i<2; i++)
                            {
                                opTemp[i] = c;
                                c = fgetc(objFile);
                                charCtr++;
                            }
                            opTemp[2]='\0';
                            tempTA = ((int)strtol(opTemp, NULL, 16));
                            struct instruction tempInstr;
                            tempInstr.address = addressCtr;
                            tempInstr.opCode = tempOP;
                            tempInstr.format = 2;
                            tempInstr.ta = tempTA;
                            tempInstr.hasSym = 0;
                            instrLib[instrCtr] = tempInstr;
                            instrCtr++;
                            addressCtr += tempInstr.format;
                        }
                    }
                    //otherwise bitmask the opcode and check if it is a format 3/4 instruction
                    else if(validOpcode((((int)strtol(opTemp, NULL, 16)) & FC)) == 1)
                    {           
                        //bitmask to obtain opcode and save it in a temp variable
                        tempOP = ((int)strtol(opTemp, NULL, 16)) & FC;

                        //bitmask to obtain n/i flag bits
                        tempNI = ((int)strtol(opTemp, NULL, 16)) & 3;

                        //Check the xbpe flag bits, specifically search for extended format and parse accordingly
                        opTemp[0] = '0';
                        opTemp[1] = c;
                        opTemp[2]='\0';

                        tempXBPE = ((int)strtol(opTemp, NULL, 16));

                        //if extended format, skip next 5 chars, else only skip 3
                        if(c == '1' || c == '9')
                        {   
                            c = fgetc(objFile);
                            charCtr++;
                            for(i = 0; i<5; i++)
                            {
                                taTempA[i] = c;
                                c = fgetc(objFile);
                                charCtr++;
                            }
                            taTempA[5] = '\0';
                            tempTA = (int)strtol(taTempA, NULL, 16);
                            tempFormat = 4;
                        }
                        else
                        {
                            c = fgetc(objFile);
                            charCtr++;
                            for(i = 0; i<3; i++)
                            {
                                taTempB[i] = c;
                                c = fgetc(objFile);
                                charCtr++;
                            }
                            taTempB[3] = '\0';
                            tempTA = (int)strtol(taTempB, NULL, 16);
                            tempFormat = 3;
                        }
                        //create new data struct and add to instruction library
                        struct instruction tempInstr;
                        tempInstr.address = addressCtr;
                        tempInstr.opCode = tempOP;
                        if(tempOP == 4)
                        {
                            X = tempTA;
                        }
                        tempInstr.mnemonic = getMnemonic(tempOP);
                        tempInstr.ni = tempNI;
                        tempInstr.xbpe = tempXBPE;
                        tempInstr.format = tempFormat;
                        tempInstr.ta = tempTA;
                        tempInstr.hasSym = 0;
                        instrLib[instrCtr] = tempInstr;
                        instrCtr++;
                        addressCtr += tempInstr.format;
                        //end of current instruction
                    }
                }
                //end of current Text record
            }

            if(c == 'M')
            {   
                for(i=0; i<6 ;i++)
                {
                    c = fgetc(objFile);
                    tempModR[i] = c;
                }
                tempModR[6] = '\0';
                modRec[modCtr] = (int)strtol(tempModR, NULL, 16);
                modCtr++;
                while(c != '\n')
                {
                    c = fgetc(objFile);
                }
            }

            //END record, parse and record the address of the first executable instruction
            if(c == 'E')
            {
                for(i=0; i<6 ;i++)
                {
                    c = fgetc(objFile);
                    firstInstr[i] = c;
                }
                firstInstr[6] = '\0';
                firstExec = (int)strtol(firstInstr, NULL, 16);
            }
        }
    }//End of .obj file parsing
    lastInstr = instrCtr;
    fclose(objFile);

//**********************************************************
//Add symbols to the instruction Structs that require them
//**********************************************************
    int j;
    int symAdded = 0;
    for(i=1; i< instrCtr ;i++)
    {   
        for(j=0; j<symCount; j++)
        {
            if((int)strtol(symtable[j].value, NULL, 16) == instrLib[i].address)
            {
                instrLib[i].symbol = getSymbol(symtable, instrLib[i].address);
                instrLib[i].hasSym = 1;
                symAdded++;
            }
        }
    }


//***********************************
//Add remaining symbols from symtab
//***********************************
    for(i=symAdded; i<symCount+1;i++)
    {
        struct instruction tempInstr;
        tempInstr.address = (int)strtol(symtable[i].value, NULL, 16);
        tempInstr.symbol = symtable[i].symbol;
        tempInstr.format = 6;
        tempInstr.hasSym = 1;
        tempInstr.mnemonic = "RESW";
        instrLib[instrCtr] = tempInstr;
        instrCtr++;
    }
    struct instruction tempInstr;
    tempInstr.address = endAdr;
    tempInstr.symbol = "END";
    tempInstr.mnemonic = getSymbol(symtable, firstExec);
    tempInstr.hasSym = 1;
    tempInstr.format = 7;
    instrLib[instrCtr] = tempInstr;
    instrCtr++;

//*********************************
//Calculate RESW decimal Values
//*********************************
    for(i=lastInstr; i<instrCtr-1;i++)
    {
        instrLib[i].reserve = (instrLib[i+1].address - instrLib[i].address)/3;
    }
    
//***************************************
//Various Addressing mode calculations
//***************************************
    for(i=0; i<instrCtr ;i++)
    {
        //check to see if the struct at instructionLibrary[i] is actually an instruction
        if(instrLib[i].format == 3)
        {
            //immediate addressing
            if(instrLib[i].ni == 1)
            {
                if(instrLib[i].xbpe == 0)
                {
                    instrLib[i].displacement = instrLib[i].ta;
                }
                if(instrLib[i].xbpe == 2)
                {
                    if(getLitaddr(literals,instrLib[i+1].address)!= 999999)
                    {
                        //if the address of the next instruction is a literal, add the literal to the operand
                        instrLib[i].operand = getLiteral(literals,instrLib[i+1].address); 
                    }
                    //otherwise calculate the displacement and find the symbol 
                    else
                    {
                        instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address + instrLib[i].ta) & 0x0FFF);
                    }
                }
                if(instrLib[i].xbpe == 4)
                {
                    instrLib[i].operand = getSymbol(symtable, (instrLib[i].ta + BASE));
                }

            }
            //indirect addressing
            if(instrLib[i].ni == 2)
            {
                if(instrLib[i].xbpe == 0)
                {
                    instrLib[i].displacement = instrLib[i].ta;
                }
                if(instrLib[i].xbpe == 2)
                {
                    if(getLitaddr(literals,instrLib[i+1].address)!= 999999)
                    {
                        //if the address of the next instruction is a literal, add the literal to the operand
                        instrLib[i].operand = getLiteral(literals,instrLib[i+1].address); 
                    }
                    //otherwise calculate the displacement and find the symbol 
                    else
                    {
                        instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address + instrLib[i].ta) & 0x0FFF);
                    }
                }
                if(instrLib[i].xbpe == 4)
                {
                    instrLib[i].operand = getSymbol(symtable, (instrLib[i].ta + BASE));
                }
            }
            //simple addressing
            if(instrLib[i].ni == 3)
            {
                if(instrLib[i].xbpe == 0)
                {
                    instrLib[i].displacement = instrLib[i].ta; 
                }
                if(instrLib[i].xbpe == 2)
                {
                    if(getLitaddr(literals,instrLib[i+1].address)!= 999999)
                    {
                        //if the address of the next instruction is a literal, add the literal to the operand
                        instrLib[i].operand = getLiteral(literals,instrLib[i+1].address); 
                    }
                    //otherwise calculate the displacement and find the symbol 
                    else
                    {
                        if (instrLib[i].ta > 0xF00)
                        {
                            instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address + instrLib[i].ta) & 0x0FFF);
                        }
                        else if(instrLib[i].opCode == 56 && instrLib[i].ta < 0xF00)
                        {
                            instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address - instrLib[i].ta));
                        }
                        else
                        {
                            if(symContains(symtable, (instrLib[i+1].address + instrLib[i].ta))==0)
                            {
                                instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address - instrLib[i].ta));
                            }
                            else if (symContains(symtable, (instrLib[i+1].address + instrLib[i].ta))==1)
                            {
                                instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address + instrLib[i].ta));
                            }
                        }
                        
                    }
                }
                if(instrLib[i].xbpe == 4)
                {
                    instrLib[i].operand = getSymbol(symtable, (instrLib[i].ta + BASE));
                }
                if(instrLib[i].xbpe == 8)
                {
                    instrLib[i].displacement = instrLib[i].ta + X;
                }
                if(instrLib[i].xbpe == 10)
                {
                    instrLib[i].operand = getSymbol(symtable, (instrLib[i+1].address + instrLib[i].ta + X));
                }
                if(instrLib[i].xbpe == 12)
                {
                    instrLib[i].displacement = instrLib[i].ta - BASE - X;
                    if (BASE + instrLib[i].displacement == 0)
                    {
                        instrLib[i].operand = getSymbol(symtable, (BASE));
                    }
                    else
                    {
                        instrLib[i].operand = getSymbol(symtable, (BASE + instrLib[i].displacement));
                    }
                }
            }
        }
        //format 4 instruction --> e flag bit = 1
        if(instrLib[i].format == 4)
        {
            //immediate addressing
            if(instrLib[i].ni == 1)
            {
                if(instrLib[i].xbpe == 1)
                {
                    instrLib[i].operand = getSymbol(symtable, instrLib[i].ta);
                    if(instrLib[i].opCode == 0x68)
                    {
                        if(getSymboladr(symtable, instrLib[i].operand) != 99999)
                        {
                            BASE = getSymboladr(symtable, instrLib[i].operand);
                        }
                    }
                }
            }
            //indirect addressing
            if(instrLib[i].ni == 2)
            {
                if(instrLib[i].xbpe == 1)
                {
                    instrLib[i].operand = getSymbol(symtable, instrLib[i].ta);
                }
            }
            //simple addressing
            if(instrLib[i].ni == 3)
            {
                if(instrLib[i].xbpe == 1)
                {
                    instrLib[i].operand = getSymbol(symtable, instrLib[i].ta);
                }
                if(instrLib[i].xbpe == 9)
                {
                    instrLib[i].operand = getSymbol(symtable, instrLib[i].ta);
                    strcat(instrLib[i].operand,",X");
                }
            }
        }
    }
 
//*****************************
//Printing .lis format
//*****************************
    int spaces;
    char lis [12];
    for(i=0; i< strLength;i++)
    {   
        lis[i] = argv[1][i];
        fctr++;
    }
    lis[fctr] = '.';
    fctr++;
    lis[fctr] = 'l';
    fctr++;
    lis[fctr] = 'i';
    fctr++;
    lis[fctr] = 's';
    fctr++;
    lis[fctr] = '\0';
    fctr = 0;

    printf("\nCreating %s file in current directory...\n\n", lis);

    FILE *lisfile;
    lisfile = fopen(lis, "w");

    for(i=0; i< instrCtr ;i++)
    {   
        //print Format 4 instruction
        if(instrLib[i].format == 4)
        {
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile,"%06X      ", instrLib[i].address);
            //check if a symbol needs to be printed
            if(instrLib[i].hasSym == 1)
            {
                printf("%s",instrLib[i].symbol);
                fprintf(lisfile, "%s", instrLib[i].symbol);
                for(j=0;j<(10-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                printf("+");
                fprintf(lisfile, "+");
            }
            else
            {
                for(j=0; j<(10); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                printf("+");
                fprintf(lisfile, "+");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(lisfile, "%s", instrLib[i].mnemonic);
            for(j=0;j<(9-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            //check addressing mode
            if(instrLib[i].ni == 1)//immediate address #
            {   
                printf("#%s", instrLib[i].operand);
                fprintf(lisfile, "#%s", instrLib[i].operand);
            }
            else if(instrLib[i].ni == 2)//indirect address @
            {
                printf("@%s", instrLib[i].operand);
                fprintf(lisfile, "@%s", instrLib[i].operand);
            }
            else
            {  
                printf(" %s", instrLib[i].operand);
                fprintf(lisfile, " %s", instrLib[i].operand);
            }
            //operand
            for(j=0; j<(16-strlen(instrLib[i].operand)); j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            printf("%02X%X%05X\n", (instrLib[i].opCode + instrLib[i].ni), instrLib[i].xbpe, instrLib[i].ta);
            fprintf(lisfile, "%02X%X%05X\n", (instrLib[i].opCode + instrLib[i].ni), instrLib[i].xbpe, instrLib[i].ta);
            //newline for LDB 
            if(instrLib[i].opCode == 0x68)
            {
                for(j=0;j<(12);j++)
                {
                    printf(" ");
                    fprintf(lisfile," ");
                }
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(lisfile," ");
                }
                printf("BASE");
                fprintf(lisfile, "BASE");
                for(j=0;j<(10-4);j++)
                {
                    printf(" ");
                    fprintf(lisfile," ");
                }
                printf("%s\n",instrLib[i].operand);
                fprintf(lisfile, "%s\n",instrLib[i].operand);
            }
        }
        //print LITERAL
        else if(instrLib[i].format == 0)//print literal
        {
            //print LTORG
            for(j=0;j<(12);j++)
            {
                printf(" ");
                fprintf(lisfile," ");
            }
            for(j=0; j<(11); j++)
            {
                printf(" ");
                fprintf(lisfile," ");
            }
            printf("LTORG\n");
            fprintf(lisfile, "LTORG\n");

            //print literal
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile, "%06X      ", instrLib[i].address);
            for(j=0; j<(11); j++)
            {
                printf(" ");
                fprintf(lisfile," ");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(lisfile,"%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(lisfile," ");
            }
            printf("%s", instrLib[i].operand);
            fprintf(lisfile, "%s", instrLib[i].operand);
            for(j=0;j<(16-strlen(instrLib[i].operand));j++)
            {
                printf(" ");
                fprintf(lisfile," ");
            }
            printf("%X\n",instrLib[i].literal);
            fprintf(lisfile, "%X\n",instrLib[i].literal);
        }
        //START + Program Name
        else if(instrLib[i].format == 5)
        {
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile, "%06X      ", instrLib[i].address);
            printf("%s",instrLib[i].symbol);
            fprintf(lisfile, "%s",instrLib[i].symbol);
            for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(lisfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            printf("%X\n", instrLib[i].address);
            fprintf(lisfile, "%X\n", instrLib[i].address);
        }
        //print remaining Symbols and values
        else if(instrLib[i].format == 6)
        {
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile, "%06X      ", instrLib[i].address);
            if(instrLib[i].symbol != NULL)
            {
                printf("%s",getSymbol(symtable, instrLib[i].address));
                fprintf(lisfile, "%s",getSymbol(symtable, instrLib[i].address));
                for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            else
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(lisfile,"%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            printf("%d\n",instrLib[i].reserve);
            fprintf(lisfile, "%d\n",instrLib[i].reserve);
        }
        //print END Symbol
        else if(instrLib[i].format == 7)
        {
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile, "%06X      ", instrLib[i].address);
            if(instrLib[i].symbol != NULL)
            {
                printf("%s",instrLib[i].symbol);
                fprintf(lisfile, "%s",instrLib[i].symbol);
                for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            else
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            printf("%s\n",instrLib[i].mnemonic);
            fprintf(lisfile, "%s\n",instrLib[i].mnemonic);
        }
        //IF format 3 instruction
        else if(instrLib[i].format == 3)
        {
            printf("%06X      ", instrLib[i].address);
            fprintf(lisfile, "%06X      ", instrLib[i].address);
            if(instrLib[i].hasSym == 1)
            {
                printf("%s",getSymbol(symtable, instrLib[i].address));
                fprintf(lisfile, "%s",getSymbol(symtable, instrLib[i].address));
                for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            else
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(lisfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(9-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(lisfile, " ");
            }
            //check addressing mode
            if(instrLib[i].ni == 1)//immediate address #
            {   
                printf("#%d",instrLib[i].ta);
                fprintf(lisfile, "#%d",instrLib[i].ta);
                if(instrLib[i].ta < 10)
                {
                    spaces = 1;
                }
                else if(instrLib[i].ta < 100)
                {
                    spaces = 2;
                }
                else if(instrLib[i].ta < 1000)
                {
                    spaces = 3;
                }
                for(j=0; j<(16-spaces); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                spaces = 0;
            }
            else if(instrLib[i].ni == 2)//indirect address @
            {
                printf("@");
                fprintf(lisfile, "@");
                spaces = 0;
                for(j=0; j<(16); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
            }
            else//ni = 3
            {
                //ni = and xbpe = 0
                if (instrLib[i].xbpe == 0)
                {
                    if(instrLib[i].opCode == 0x4C)
                    {
                        //do nothing because RSUB doesnt print an operand
                        for(j=0; j<(17); j++)
                        {
                            printf(" ");
                            fprintf(lisfile, " ");
                        }
                    }
                    else
                    {
                        printf(" %d",instrLib[i].ta);
                        fprintf(lisfile, " %d",instrLib[i].ta);
                        if(instrLib[i].ta < 10)
                        {
                            spaces = 1;
                        }
                        else if(instrLib[i].ta < 100)
                        {
                            spaces = 2;
                        }
                        else if(instrLib[i].ta < 1000)
                        {
                            spaces = 3;
                        }
                        for(j=0; j<(16-spaces); j++)
                        {
                            printf(" ");
                            fprintf(lisfile, " ");
                        }
                    }
                }
                else if (instrLib[i].xbpe == 2)
                {
                    printf(" %s",instrLib[i].operand);
                    fprintf(lisfile, " %s",instrLib[i].operand);
                    for(j=0; j<(16-strlen(instrLib[i].operand)); j++)
                    {
                        printf(" ");
                        fprintf(lisfile, " ");
                    }
                }
                else if (instrLib[i].xbpe == 4)
                {
                    //double check
                    printf(" %d",instrLib[i].operand);
                    fprintf(lisfile, " %d",instrLib[i].operand);
                    for(j=0; j<(14-strlen(instrLib[i].operand)); j++)
                    {
                        printf(" ");
                        fprintf(lisfile, " ");
                    }
                }
                else if (instrLib[i].xbpe == 8)
                {
                    printf(" %d,X",instrLib[i].displacement);
                    fprintf(lisfile, " %d,X",instrLib[i].displacement);
                    if(instrLib[i].displacement < 10)
                    {
                        spaces = 1;
                    }
                    else if(instrLib[i].displacement < 100)
                    {
                        spaces = 2;
                    }
                    else if(instrLib[i].displacement < 1000)
                    {
                        spaces = 3;
                    }
                    for(j=0; j<(14-spaces); j++)
                    {
                        printf(" ");
                        fprintf(lisfile, " ");
                    }
                }
                else if (instrLib[i].xbpe == 10)
                {
                    printf(" %s,X",instrLib[i].operand);
                    fprintf(lisfile, " %s,X",instrLib[i].operand);
                    for(j=0; j<(14-strlen(instrLib[i].operand)); j++)
                    {
                        printf(" ");
                        fprintf(lisfile, " ");
                    }
                }
                else if (instrLib[i].xbpe == 12)
                {
                    printf(" %s,X",instrLib[i].operand);
                    fprintf(lisfile, " %s,X",instrLib[i].operand);
                    for(j=0; j<(14-strlen(instrLib[i].operand)); j++)
                    {
                        printf(" ");
                        fprintf(lisfile, " ");
                    }
                }
            }
            //operand

            printf("%02X%X%03X\n", (instrLib[i].opCode + instrLib[i].ni), instrLib[i].xbpe, instrLib[i].ta);
            fprintf(lisfile, "%02X%X%03X\n", (instrLib[i].opCode + instrLib[i].ni), instrLib[i].xbpe, instrLib[i].ta);
            //print newline for BASE register
            if(instrLib[i].opCode == 0x68)
            {
                for(j=0;j<(12);j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                printf("BASE");
                fprintf(lisfile, "BASE");  
                for(j=0;j<(10-4);j++)
                {
                    printf(" ");
                    fprintf(lisfile, " ");
                }
                printf("\n");
                fprintf(lisfile, "\n");
            }
        }
    }
    printf("\n");
    fclose(lisfile);

//*****************************
//Printing .sic format
//*****************************
    char sicOutput [12];
    for(i=0; i< strlen(argv[1]);i++)
    {   
        sicOutput[i] = argv[1][i];
        fctr++;
    }
    sicOutput[fctr] = '.';
    fctr++;
    sicOutput[fctr] = 's';
    fctr++;
    sicOutput[fctr] = 'i';
    fctr++;
    sicOutput[fctr] = 'c';
    fctr++;
    sicOutput[fctr] = '\0';
    fctr = 0;

    printf("\nCreating %s file in current directory...\n\n", sicOutput);

    FILE *sicfile;
    sicfile = fopen(sicOutput, "w");

    for(i=0; i< instrCtr ;i++)
    {   
        //print Format 4 instruction
        if(instrLib[i].format == 4)
        {
            if(instrLib[i].hasSym == 1)
            {
                printf("%s",instrLib[i].symbol);
                fprintf(sicfile, "%s",instrLib[i].symbol);
                for(j=0;j<(10-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("+");
                fprintf(sicfile, "+");
            }
            else
            {
                for(j=0; j<(10); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("+");
                fprintf(sicfile, "+");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(sicfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(9-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            //check addressing mode
            if(instrLib[i].ni == 1)//immediate address #
            {   
                printf("#%s", instrLib[i].operand);
                fprintf(sicfile, "#%s", instrLib[i].operand);
            }
            else if(instrLib[i].ni == 2)//indirect address @
            {
                printf("@%s", instrLib[i].operand);
                fprintf(sicfile, "@%s", instrLib[i].operand);
            }
            else
            {  
                printf(" %s", instrLib[i].operand);
                fprintf(sicfile, " %s", instrLib[i].operand);
            }
            //operand
            printf("\n");
            fprintf(sicfile, "\n");

            //newline for LDB 
            if(instrLib[i].opCode == 0x68)
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("BASE");
                fprintf(sicfile, "BASE");
                for(j=0;j<(10-4);j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("%s\n",instrLib[i].operand);
                fprintf(sicfile, "%s\n",instrLib[i].operand);
            }
        }
        //print LITERAL
        else if(instrLib[i].format == 0)//print literal
        {
            //print LTORG
            for(j=0; j<(11); j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("LTORG\n");
            fprintf(sicfile, "LTORG\n");
            //print literal
            for(j=0; j<(11); j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(sicfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("%s\n", instrLib[i].operand);
            fprintf(sicfile, "%s\n", instrLib[i].operand);
        }
        //START + Program Name
        else if(instrLib[i].format == 5)
        {
            printf("%s",instrLib[i].symbol);
            fprintf(sicfile, "%s",instrLib[i].symbol);
            for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(sicfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("%X\n", instrLib[i].address);
            fprintf(sicfile, "%X\n", instrLib[i].address);
        }
        //print remaining Symbols and values
        else if(instrLib[i].format == 6)
        {
            if(instrLib[i].symbol != NULL)
            {
                printf("%s",getSymbol(symtable, instrLib[i].address));
                fprintf(sicfile, "%s",getSymbol(symtable, instrLib[i].address));
                for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            else
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(sicfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(10-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }
            printf("%d\n",instrLib[i].reserve);
            fprintf(sicfile, "%d\n",instrLib[i].reserve);
        }
        //print END Symbol
        else if(instrLib[i].format == 7)
        {
            if(instrLib[i].symbol != NULL)
            {
                printf("           %s",instrLib[i].symbol);
                fprintf(sicfile, "           %s",instrLib[i].symbol);
                for(j=0;j<(10-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            else
            {
                for(j=0; j<(10); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            printf("%s\n",instrLib[i].mnemonic);
            fprintf(sicfile, "%s\n",instrLib[i].mnemonic);
        }
        //IF format 3 instruction
        else if(instrLib[i].format == 3)
        {
            if(instrLib[i].hasSym == 1)
            {
                printf("%s",getSymbol(symtable, instrLib[i].address));
                fprintf(sicfile, "%s",getSymbol(symtable, instrLib[i].address));
                for(j=0;j<(11-strlen(instrLib[i].symbol));j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            else
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            printf("%s",instrLib[i].mnemonic);
            fprintf(sicfile, "%s",instrLib[i].mnemonic);
            for(j=0;j<(9-strlen(instrLib[i].mnemonic));j++)
            {
                printf(" ");
                fprintf(sicfile, " ");
            }

            //check addressing mode
            if(instrLib[i].ni == 1)//immediate address #
            {   
                printf("#%d\n",instrLib[i].ta);
                fprintf(sicfile, "#%d\n",instrLib[i].ta);
            }
            else if(instrLib[i].ni == 2)//indirect address @
            {
                printf("@");
                fprintf(sicfile, "@");
                for(j=0; j<(16); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
            }
            else//ni = 3
            {
                //ni = and xbpe = 0
                if (instrLib[i].xbpe == 0)
                {
                    if(instrLib[i].opCode == 0x4C)
                    {
                        printf("\n");
                        fprintf(sicfile, "\n");
                    }
                    else
                    {
                        printf(" %d\n",instrLib[i].ta);
                        fprintf(sicfile, " %d\n",instrLib[i].ta);
                    }
                }
                else if (instrLib[i].xbpe == 2)
                {
                    printf(" %s\n",instrLib[i].operand);
                    fprintf(sicfile, " %s\n",instrLib[i].operand);

                }
                else if (instrLib[i].xbpe == 4)
                {
                    printf(" %d\n",instrLib[i].operand);
                    fprintf(sicfile, " %d\n",instrLib[i].operand);

                }
                else if (instrLib[i].xbpe == 8)
                {
                    printf(" %d,X\n",instrLib[i].displacement);
                    fprintf(sicfile, " %d,X\n",instrLib[i].displacement);
                }
                else if (instrLib[i].xbpe == 10)
                {
                    printf(" %s,X\n",instrLib[i].operand);
                    fprintf(sicfile, " %s,X\n",instrLib[i].operand);
                }
                else if (instrLib[i].xbpe == 12)
                {
                    printf(" %s,X\n",instrLib[i].operand);
                    fprintf(sicfile, " %s,X\n",instrLib[i].operand);
                }
            }
            //operand
            if(instrLib[i].opCode == 0x68)
            {
                for(j=0; j<(11); j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("BASE");
                fprintf(sicfile,"BASE");
                for(j=0;j<(10-4);j++)
                {
                    printf(" ");
                    fprintf(sicfile, " ");
                }
                printf("\n");
                fprintf(sicfile, "BASE");
            }
        }
    }
    printf("\n");
    fclose(sicfile);
    return 0;
}