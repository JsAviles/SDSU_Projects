/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #3
* File:        	pagetables.h
* Description:  Header file for pagetables.cpp
*************************************************************************************/

#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "helpers.h"
#include "byutr.h"
#include <cstring>

#define MAX_PAGEBITS 32

//PageTable Struct
struct PageTable{
	unsigned int hit;
	unsigned int miss;
	unsigned int bytes;
    int levels;
    unsigned int *BitmaskAr;
    int *ShiftAr;
    unsigned int *EntryCount;
	struct Level *RootNodePtr;
	unsigned int *AddressAr;
	unsigned int AddressCtr;
};

//Map Struct
struct MAP{
    bool Validity = false;
    unsigned int Frame = 0xFFFFFFFF;
};

//Level Struct
struct Level{
    struct PageTable *PageTablePtr;
    int Depth;
    struct MAP *MapPtr;
	struct Level **NextLevelPtr;
};

/*
* Name:	    LogicalToPage
* Desc:     Given a logical address, a fixed uint32_t mask value and number of bits to shift, return translation:
*		    logical address -> page #
* Return:	unsigned int
*/
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, int Shift);

/*
* Name:	 	PageLookup
* Desc: 	Given a PageTable ptr and logical address, return:
* 				• MAP * if the entry exists
*								or
*				• NULL if the entry does not exist
* Return:	MAP *
*/
MAP * PageLookup(PageTable *PageTable, unsigned int LogicalAddress);

/*
* Name:		frameLookup
* Desc: 	Given the PageTable* and a logical address -> return the frame number associated with that logical address
* Return:	unsigned int
*/
unsigned int frameLookup(PageTable *PageTable, unsigned int LogicalAddress);

/*
* Name:		PageInsert2
* Desc: 	Given a Level*, logical address, and Frame number -> recursively call PageInsert2, traversing the page tree
*			until the Max depth is reached, and the page is mapped
* Return:	void
*/
void PageInsert2(Level *LevelPtr, unsigned int LogicalAddress, unsigned int Frame);

/*
* Name:		PageInsert
* Desc: 	Given a PageTable *, logical address, and frame number -> Establish a Level * beginning at the root node
*			and call PageInsert2 to being recursive calls for frame mapping
* Return:	void
*/
void PageInsert(PageTable *PageTable, unsigned int LogicalAddress, unsigned int Frame);

/*
* Name:		PageSetup
* Desc: 	Given number of levels, command line argument array (pDesign) containing the page level bits, and a pagetable *
*			-> Establish the following:
*										• bitmask array
*										• shift array
*										• entry count array
*										• hit counter
*										• miss counter
* Return:	void
*/
void PageSetup(int levels, int *pDesign, PageTable *pageTable);

/*
* Name:		oPrint
* Desc: 	This function is used to call upon helpers.cpp that will aid in the output to
*			the terminal. Based on the users output flag, the output will produce a 
*			summary, bitmasks, offset, logical2physical, or page2frame.
* Return:	void
*/
void oPrint(PageTable * PageTable, char * oArgument, unsigned int pSize);
