/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #2
* File:        	wordcount.cpp
* Description:  Source code for "poor mans progress bar"
*************************************************************************************/

#include "wordcount.h"

typedef struct{   
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

//worker thread
void * progress_monitor (void * voidPtr){
    long term = ((PROGRESS_STATUS *) voidPtr)->TerminationValue;

    //Counter used to track printing of '-' or '+'.
    int ctr = 0;

    //Progress tracker in %
    int progCtr = 1;

    //while loop to keep checking the progress of Currentstatus --> then print accordingly
    while(progCtr <=100){
        //check if the percentage of bytes read is larger than the next threshold
        if(((long)*((PROGRESS_STATUS *) voidPtr)->CurrentStatus*(long)100/term)>=progCtr ){
            //print a hyphen
            if(ctr<9){
                cout << "-" << flush;
                ctr++;
            }
            //else if its the 10th char printed, print a +
            else{
                cout << "+" << flush;
                ctr=0;
            }
            //increment progCtr by 2 because for 100% we are printing 50 progress ticks.
            progCtr+=2;
        }
    }
    return NULL;
}

//main thread
long wordcount(char * filename){
    FILE * txtFile;
    //check if file exists, if not exit
    txtFile = fopen(filename, "r");
    if(txtFile == NULL){
        printf("Could not open file\n");
        return 0;
    }
    else{
        long wordCtr = 0;
        bool word;
        struct stat fSize;
        stat(filename, &fSize);

        //create instance of progress_status struct
        PROGRESS_STATUS *pStat = new PROGRESS_STATUS;
        pStat->CurrentStatus = new long(0);
        pStat->InitialValue = 0;
        pStat->TerminationValue = fSize.st_size;

        //Create progress_monitor thread
        pthread_t workerThread;
        pthread_create(&workerThread, NULL, &progress_monitor, (void *) pStat);

        //parse the file and update bytes (chars) and count words
        char c = getc(txtFile);
        //set flag for checking words
        if(iswspace(c)){
            word = true;
        }
        else{
            word = false;
        }

        while(c != EOF){
            *pStat->CurrentStatus+=1;
            //if a space is encountered, increment wordCounter
            if(iswspace(c) && !word){
                wordCtr++;
                word = true;
            }
            //else if the char is not a space...meaning its the start of the next word, switch the flag
            else if(!iswspace(c)){
                word = false;
            }
            c = getc(txtFile);
        }
        if (!word){
            wordCtr++;
        }

        //wait for progress_monitor to finish printing then return and print the # of words
        pthread_join(workerThread, NULL);
        fclose(txtFile);
        return wordCtr;
    }
}

int main (int argc, char* argv[]){
    //file/argument error checking
    if(argc<2){
        printf("No file specified\n");
    }
    else if (argc > 2){
        printf("Too many arguments specified\n");
    }
    else{
        FILE * txtFile;
        //check if file exists, if not exit
        txtFile = fopen(argv[1], "r");
        if(txtFile == NULL){
            printf("Could not open file\n");
            return 0;
        }
        else{
            struct stat fSize;
            stat(argv[1], &fSize);

            if (fSize.st_size ==0){
                printf("Files is empty\n");
                return 0;
            }
            fclose(txtFile);
            printf("\nThere are %ld words in %s.\n", wordcount(argv[1]), argv[1]);
        }
    }
    return 0;
}