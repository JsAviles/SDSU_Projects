/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #3
* File:        	pagetables.cpp
* Description:  This program will simulate the workings of how multilevel paging works
* 				by creating page tables with varying depths. The purpose of this
*				exercise is to mimic the tracing of virtual addresses and the process
*				of translating and storing into physical addresses. This file must be
*				compiled along with the given files helpers.cpp and byu_tracereader.c
*************************************************************************************/

#include "pagetable.h"

/*
* Name:	    LogicalToPage
* Desc:     Given a logical address, a fixed uint32_t mask value and number of bits to shift, return translation:
*		    logical address -> page #
* Return:	unsigned int
*/
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, int Shift){
    return ((LogicalAddress & Mask)>>Shift);
}

/*
* Name:	 	PageLookup
* Desc: 	Given a PageTable ptr and logical address, return:
* 				• MAP * if the entry exists
*								or
*				• NULL if the entry does not exist
* Return:	MAP *
*/
MAP * PageLookup(PageTable *PageTable, unsigned int LogicalAddress){
	unsigned int vpn = LogicalToPage(LogicalAddress, PageTable->BitmaskAr[PageTable->RootNodePtr->Depth], PageTable->ShiftAr[PageTable->RootNodePtr->Depth]);
	MAP *temp = NULL;
	//If # of levels > 1 and the nextlevel index for the vpn is NULL -> return NULL
	if(PageTable->RootNodePtr->NextLevelPtr[vpn] == NULL & PageTable->levels > 1){
		return NULL;
	}
	//If # of levels == 1 (single level paging) -> step in
	else if(PageTable->levels == 1){
		//If the MAP* index for the vpn is the default value (the highest value of uint32_t) -> temp = NULL
		if(PageTable->RootNodePtr->MapPtr[vpn].Frame == 0xFFFFFFFF){
			return temp;
		}
		//Else if the entry does exist -> set temp to the MAP * and return temp
		else{
			temp = PageTable->RootNodePtr->MapPtr;
			return temp;
		}
	}
	//If multi-level paging and the rootnode nextlevel* at index (vpn) is not NULL -> Step through the Page tree
	else{
		//Set a LevelPtr equal to the next page level entry
		Level *LevelPtr = PageTable->RootNodePtr->NextLevelPtr[vpn];
		//For loop to step through the tree for # of Page levels
		for(int i=1; i<(PageTable->levels); i++ ){	
			//Set the current vpn	
			vpn = LogicalToPage(LogicalAddress, PageTable->BitmaskAr[i], PageTable->ShiftAr[i]);
			//If the current level is the max depth -> step in and check the Map*
			if((i+1)==(PageTable->levels)){
				//Same if/else case as lines 44-51
				if(LevelPtr->MapPtr[vpn].Frame == 0xFFFFFFFF){
					return temp;
				}
				else{
					temp = LevelPtr->MapPtr;
					return temp;
				}
			}
			//If the path for the vpn is NULL -> return NULL
			else if(LevelPtr->NextLevelPtr[vpn] == NULL){
				return temp;
			}
			//Set Levelptr to the Next Level node
			LevelPtr = LevelPtr->NextLevelPtr[vpn];
		}
		return temp;
	}
}

/*
* Name:		frameLookup
* Desc: 	Given the PageTable* and a logical address -> return the frame number associated with that logical address
* Return:	unsigned int
*/
unsigned int frameLookup(PageTable *PageTable, unsigned int LogicalAddress)
{
	unsigned int vpn = LogicalToPage(LogicalAddress, PageTable->BitmaskAr[PageTable->RootNodePtr->Depth], PageTable->ShiftAr[PageTable->RootNodePtr->Depth]);
	unsigned int temp = 0;
	//If multi-level paging, check if path is NULL for first vpn
	if(PageTable->RootNodePtr->NextLevelPtr[vpn] == NULL & PageTable->levels > 1){
		return temp;
	}
	//If Single level paging -> Step in and check rootnodes MAP*
	else if(PageTable->levels == 1){
		//if the page is not mapped -> return NULL
		if(PageTable->RootNodePtr->MapPtr[vpn].Frame == 0xFFFFFFFF){
			return temp;
		}
		//else set temp to the mapped frame # and return temp
		else{
			temp = PageTable->RootNodePtr->MapPtr[vpn].Frame;
			return temp;
		}
	}
	//Else, step through the tree to max Depth
	else{
		int i;
		//Set a LevelPtr equal to the next depth level
		Level *LevelPtr = PageTable->RootNodePtr->NextLevelPtr[vpn];
		for(i=1; i<(PageTable->levels); i++ ){	
			//Update the vpn for current depth
			vpn = LogicalToPage(LogicalAddress, PageTable->BitmaskAr[i], PageTable->ShiftAr[i]);
			//If the current depth is max depth -> step in and check if frame is mapped
			if((i+1)==(PageTable->levels)){
				//If the frame is not mapped -> return NULL
				if(LevelPtr->MapPtr[vpn].Frame == 0xFFFFFFFF){
					return temp;
				}
				//else return the mapped frame #
				else{
					temp = LevelPtr->MapPtr[vpn].Frame;
					return temp;
				}
			}
			//Set Level ptr to the next levels node
			LevelPtr = LevelPtr->NextLevelPtr[vpn];
		}
		return temp;
	}
}

/*
* Name:		PageInsert2
* Desc: 	Given a Level*, logical address, and Frame number -> recursively call PageInsert2, traversing the page tree
*			until the Max depth is reached, and the page is mapped
* Return:	void
*/
void PageInsert2(Level *LevelPtr, unsigned int LogicalAddress, unsigned int Frame){
	//Calculate vpn
	unsigned int vpn = LogicalToPage(LogicalAddress, LevelPtr->PageTablePtr->BitmaskAr[LevelPtr->Depth],LevelPtr->PageTablePtr->ShiftAr[LevelPtr->Depth]);
	//If the current Depth is the max Depth -> Step in and map the vpn
	if(LevelPtr->Depth == (LevelPtr->PageTablePtr->levels-1)){
		//If the MAP* is NULL (Map does not exist) -> Instantiate the MAP* and map the VPN
		if(LevelPtr->MapPtr == NULL){
			LevelPtr->MapPtr = new MAP [LevelPtr->PageTablePtr->EntryCount[LevelPtr->Depth]];
			LevelPtr->PageTablePtr->bytes += sizeof(MAP);//increment total bytes
			LevelPtr->MapPtr[vpn].Frame = Frame;
			LevelPtr->MapPtr[vpn].Validity = true;
			LevelPtr->PageTablePtr->bytes += sizeof(MAP);//increment total bytes
		}
		//Else just MAP the VPN
		else{
			LevelPtr->MapPtr[vpn].Frame = Frame;
			LevelPtr->MapPtr[vpn].Validity = true;
			LevelPtr->PageTablePtr->bytes += sizeof(MAP);//increment total bytes
		}
	}
	//If not at max tree depth -> continue traversing 
	else{
		//If vpn entry does not exist, create it and continue traversing
		if(LevelPtr->NextLevelPtr[vpn] == NULL){
			LevelPtr->NextLevelPtr[vpn] = new Level;

			LevelPtr->PageTablePtr->bytes += sizeof(Level);//increment total bytes

			LevelPtr->NextLevelPtr[vpn]->Depth = LevelPtr->Depth+1;
			LevelPtr->NextLevelPtr[vpn]->NextLevelPtr = new Level* [LevelPtr->PageTablePtr->EntryCount[LevelPtr->Depth+1]];

			LevelPtr->PageTablePtr->bytes += sizeof(Level*);//increment total bytes

			LevelPtr->NextLevelPtr[vpn]->PageTablePtr = LevelPtr->PageTablePtr;
			PageInsert2(LevelPtr->NextLevelPtr[vpn], LogicalAddress, Frame);
		}
		//Else if the path exists, continue traversing
		else{
			PageInsert2(LevelPtr->NextLevelPtr[vpn], LogicalAddress, Frame);
		}
	}

}

/*
* Name:		PageInsert
* Desc: 	Given a PageTable *, logical address, and frame number -> Establish a Level * beginning at the root node
*			and call PageInsert2 to being recursive calls for frame mapping
* Return:	void
*/
void PageInsert(PageTable *PageTable, unsigned int LogicalAddress, unsigned int Frame){
    PageInsert2(PageTable->RootNodePtr, LogicalAddress, Frame);
}

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
void PageSetup(int levels, int *pDesign, PageTable *pageTable){

	int temp = 0;
	int i,j;
    unsigned int prev = 0;
	pageTable->hit = 0;
	pageTable->miss = 0;

    //Algorithm to populate bitmaskAr given any page size values
    for (i=0; i<levels ;i++){
        temp+= pDesign[i];
        pageTable->BitmaskAr[i] = (pow(2,32)) - (pow(2,(32-temp))) - prev;
        prev = (pow(2,32)) - (pow(2,(32-temp)));
    }

    //Algorithm to populate the value of shifting bits for each respective level
    temp = 0;
    for (i=0; i<levels ;i++){
        temp+= pDesign[i];
        pageTable->ShiftAr[i] = 32-temp;
    }

    //Algorithm to populate # of entries to each respective level
    for (i=0; i<levels ;i++){
        pageTable->EntryCount[i] = (pow(2,pDesign[i]));
    }
}

/*
* Name:		oPrint
* Desc: 	This function is used to call upon helpers.cpp that will aid in the output to
*			the terminal. Based on the users output flag, the output will produce a 
*			summary, bitmasks, offset, logical2physical, or page2frame.
* Return:	void
*/
void oPrint(PageTable * PageTable, char * oArgument, unsigned int pSize){
	int i,j;
	unsigned int offsetMask = 0;
	unsigned int temp;
	unsigned int frame;
	uint32_t *pages = new uint32_t[PageTable->levels];
	
	//Calculate the offset Bitmasking for convenience
	for (i=0; i<PageTable->levels ;i++){
        offsetMask+= PageTable->BitmaskAr[i];
    }
	offsetMask = (pow(2,32)-1) - offsetMask;

	if(strcmp(oArgument, "bitmasks")== 0){
		report_bitmasks(PageTable->levels, PageTable->BitmaskAr);
	}
	else if(strcmp(oArgument,"offset") == 0){
		for(i=0;i<PageTable->AddressCtr;i++){
			report_logical2offset(PageTable->AddressAr[i],(PageTable->AddressAr[i] & offsetMask));
		}
	}
	else if(strcmp(oArgument, "page2frame")== 0){
		for(i=0;i<PageTable->AddressCtr;i++){
			//Populate a pages array which contains the pre calculated vpn at every level -> for every address
			for(j=0;j<PageTable->levels;j++){
				pages[j] = ((PageTable->AddressAr[i] & PageTable->BitmaskAr[j])>>PageTable->ShiftAr[j]);
			}
			temp = frameLookup(PageTable, PageTable->AddressAr[i]);
			frame = temp;
			report_pagemap(PageTable->AddressAr[i], PageTable->levels, pages, frame);
		}
	}
	else if(strcmp(oArgument, "logical2physical")== 0){
		//physical address = (Frame*pagesize) + offset
		for(i=0;i<PageTable->AddressCtr;i++){
			report_logical2physical(PageTable->AddressAr[i], ((frameLookup(PageTable, PageTable->AddressAr[i])*pSize)+(PageTable->AddressAr[i] & offsetMask)));
		}
	}
	else if(strcmp(oArgument, "summary")== 0){
		report_summary(pSize, PageTable->hit, 
		    PageTable->AddressCtr, PageTable->miss,
		    PageTable->bytes);
	}
}

/*************************************************************************************
*																					 *
*									MAIN											 *
*																					 *
*************************************************************************************/
int main(int argc, char **argv){
	//Declaration/Instatiation of variables used in main
	unsigned int opt;
	int argCtr = 0;
	int pageBits = 0;
	int i, j, levels;
	unsigned int addrCtr = 0;
	unsigned int N = 0;
	bool flag_n = false;
	bool flag_o = false;
	int* traceArgs;
	char * oArg;
	unsigned int FrameCtr = 0;
	bool done = false;

	//char* for default printing scheme in the event that user input did not yield the -o flag
	char * Default = new char[7];
	Default[0] = 's';
	Default[1] = 'u';
	Default[2] = 'm';
	Default[3] = 'm';
	Default[4] = 'a';
	Default[5] = 'r';
	Default[6] = 'y';
	Default[7] = '\0';
	
	//use getop to factor in user flags
	while ( (opt = getopt(argc, argv, "n:o:")) != -1){
		switch (opt) {
		case 'n': //number of addresses to process
			N = atoi(optarg);// optarg will contain the string following -n
			flag_n = true;
			argCtr += 2;
			break;
		case 'o': //to specify output type
			oArg = optarg;// optarg contains the output method…
			flag_o = true;
			argCtr += 2;
			break;
		default:
			exit(EXIT_FAILURE); //graceful exit if flag does not match 'o' or 'n'
		}
	}

	//READ IN TRACEFILE
	argCtr++; //increment argCtr to check if tracefile is inserted  else exit if false
	FILE *fp = fopen(argv[argCtr], "r");
	
	//check tracefile and store levels in an array
	//kick out of program if tracefile is absent
	if(argv[argCtr] == NULL){
		printf("Usage: please add tracefile\n");
		exit(EXIT_FAILURE);//graceful exit if no file given
	} 
	else if(fp == NULL){
		printf("Usage: tracefile is invalid\n");
		exit(EXIT_FAILURE);//graceful exit if file is empty	
	} 
	else{
		//values to help store
		argCtr++;
		i = 0;
		j = 0;
		//instantiate level array with user arg
		while(argv[argCtr] != NULL){
			argCtr++;
			i++;
		}
		traceArgs = new int(i);//initalize levels array
		//store value of 'i' to the variable 'levels'
		levels = i; 
		//store values into array for levels
		argCtr -= i;
		
		while(j < i){
			traceArgs[j] = atoi(argv[argCtr]);
			pageBits += atoi(argv[argCtr]);
			argCtr++;
			j++;
		}
		//check if pageBits are over 31 
		if(pageBits > (MAX_PAGEBITS -1)){
			printf("Usage: pagebits are over 31, please try again\n");
			exit(EXIT_FAILURE);
		}	
	}

	//Establish pageTable and allocate memory for member variables
	unsigned int pageSize = pow(2,MAX_PAGEBITS - pageBits);
	PageTable *pTable = new PageTable;
	pTable->bytes = 0;
	pTable->bytes += sizeof(PageTable);//increment total bytes
    pTable->levels = levels;
    pTable->BitmaskAr = new uint32_t[levels];
	pTable->bytes += sizeof(unsigned int) * levels;//increment total bytes
    pTable->ShiftAr = new int[levels];
	pTable->bytes += sizeof(unsigned int) * levels;//increment total bytes
    pTable->EntryCount = new uint32_t[levels];

	//Depending on whether or not the user gave a terminal argument for value of N, allocate the addressAr memory
	if(flag_n){
		pTable->AddressAr = new uint32_t[N];
	}
	else{
		pTable->AddressAr = new uint32_t[250000];
	}

	//Call pageSetup to initiallize/populate various PageTable arrays
	PageSetup(levels, traceArgs, pTable);

	pTable->RootNodePtr = new Level;
	pTable->bytes += sizeof(Level);//increment total bytes
	pTable->RootNodePtr->Depth = 0;
	pTable->RootNodePtr->PageTablePtr = pTable;
	pTable->RootNodePtr->NextLevelPtr = new Level* [pTable->RootNodePtr->PageTablePtr->EntryCount[0]];
	pTable->bytes += sizeof(Level*);//increment total bytes
	
	//If single level paging is indicated by user input -> instantiate the map* in the root node
	if(pTable->levels == 1){
		pTable->RootNodePtr->MapPtr = new MAP [pTable->EntryCount[0]];
		pTable->bytes += sizeof(MAP) * pTable->EntryCount[0];//increment total bytes
	}

	/* 
	* Main program while loop:
	* Trace file is read address by address, simultaneously mapping the pages
	*/

	//Structure with trace information
	p2AddrTr trace_item; 
	//While the trace file is still being read (!done)
	while(!done) 
	{
		// Grab the next address
		int bytesread = NextAddress(fp, &trace_item);
		pTable->AddressAr[addrCtr] = trace_item.addr;
		
		// Check if we actually got something
		done = bytesread == 0;
		//If given a value for -n flag (number of address to read) -> only map up to -n #
		if(flag_n){
			if (!done && addrCtr < N){		
				addrCtr++;
				//If the page entry does not exist --> Map the page and increment both: current frame and number of misses
				if(PageLookup(pTable, trace_item.addr) == NULL){
					PageInsert(pTable, trace_item.addr, FrameCtr);
					FrameCtr++;
					pTable->miss++;
				}
				//Else if the entry exists -> increment hit counter
				else{
					pTable->hit++;
				}
			}
		}
		//Else map every address in the trace file
		else if(!done){
			addrCtr += 1;
			if(PageLookup(pTable, trace_item.addr) == NULL){
				PageInsert(pTable, trace_item.addr, FrameCtr);
				FrameCtr++;
				pTable->miss++;
			}
			else{
				pTable->hit++;
			}
		}
	}
	//Update number of bytes used in address array...after reading the trace file
	pTable->AddressCtr = addrCtr;
	pTable->bytes += sizeof(unsigned int)*N;//increment total bytes

	//If a printing argument was given "-o 'print type'"-> print specified format
	if(flag_o){
		oPrint(pTable, oArg, pageSize);
	}
	//Otherwise defaults to printing the summary
	else{
		oPrint(pTable, Default, pageSize);
	}

	//close open file and exit program
	fclose(fp);
  	return (0);
}//END MAIN