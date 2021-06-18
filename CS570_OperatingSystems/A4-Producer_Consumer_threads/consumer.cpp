/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #4
* File:        	consumer.cpp
* Description:  Source code for "Consumer functionality of producer/consumer problem"
*************************************************************************************/

#include "producer_consumer.h"

/*
* Name:	    Consumer
* Desc:     consumer function which acts as the consumer thread for the Lucy and Ethel consumers
*           • consumerType is used to distinguish between which thread is which (Lucy or Ethel) and send the correct information
*             to print via io_remove_type as the first parameter
*           • if/else strcmp is used to determine which candy is being consumed, our implementation used a queue<char*> so we are reading
*             the char* at the front of the queue and consuming accordingly.
*           • Two semaphores used for mutual exclusion and to determine if there is anything to consume on the belt (bounded buffer)
* Return:	void
*/
void * Consumer(void * voidPtr){

	//Set up delay based on Dr. Roch FAQ specifications
    struct timespec	SleepTime;
	SleepTime.tv_sec = ((consumer *)voidPtr)->delay / 1000;	 //# secs
	SleepTime.tv_nsec = (((consumer *)voidPtr)->delay % 1000) * 1000000; //# nanosecs

    int consumerType = 0;

    //set the consumerType index for printing with remove_type, distinguishing between which thread is consuming
    if(strcmp(((consumer *)voidPtr)->name,"Lucy")== 0){
            consumerType = 0;
        }
        else if(strcmp(((consumer *)voidPtr)->name,"Ethel")== 0){
            consumerType = 1;
        }

    //main while loop that allows consumers to consume candies until 100 candies have been consumed
    while(!((consumer *)voidPtr)->beltPtr->finishedConsuming){
        
        //sleep for designated delay time (0 if not specified)
        nanosleep(&SleepTime, NULL);

        sem_wait(&((consumer *)voidPtr)->beltPtr->full);             
        sem_wait(&((consumer *)voidPtr)->beltPtr->mutualExclusion);   //get access to buffer
        if(!((consumer *)voidPtr)->beltPtr->finishedConsuming){

        
            //figure out which type of candy is being consumed for the counters to increment
            //check if the candy to be consumed is an escargot sucker
            if(strcmp(((consumer *)voidPtr)->beltPtr->belt.front(), "e")== 0){
                ((consumer *)voidPtr)->beltPtr->belt.pop();
                ((consumer *)voidPtr)->escargotConsumed += 1;
                ((consumer *)voidPtr)->beltPtr->candiesConsumed +=1;
                ((consumer *)voidPtr)->beltPtr->consumed[1] += 1;
                ((consumer *)voidPtr)->beltPtr->onBelt[1] -= 1;

                io_remove_type(consumerType,1,((consumer *)voidPtr)->beltPtr->onBelt, ((consumer *)voidPtr)->beltPtr->consumed);
                cout << flush;
            }
            //else if the candy to be consumed is a frog enter
            else if(strcmp(((consumer *)voidPtr)->beltPtr->belt.front(), "f")== 0){
                ((consumer *)voidPtr)->beltPtr->belt.pop();
                ((consumer *)voidPtr)->frogConsumed += 1;
                ((consumer *)voidPtr)->beltPtr->candiesConsumed += 1;
                ((consumer *)voidPtr)->beltPtr->consumed[0] += 1;
                ((consumer *)voidPtr)->beltPtr->onBelt[0] -= 1;
                
                io_remove_type(consumerType,0, ((consumer *)voidPtr)->beltPtr->onBelt, ((consumer *)voidPtr)->beltPtr->consumed);
                cout << flush;

                //if frogcapped is true, switch it back to false to allow production
                if(((consumer *)voidPtr)->beltPtr->frogCapped){
                    ((consumer *)voidPtr)->beltPtr->frogCapped = false;
                }
            }
        }

        //set consumption complete flag to true when 100 candies have been consumed
        if(((consumer *)voidPtr)->beltPtr->candiesConsumed == ((consumer *)voidPtr)->beltPtr->MAX_Produced){
            ((consumer *)voidPtr)->beltPtr->finishedConsuming = true;
        }

        sem_post(&((consumer *)voidPtr)->beltPtr->mutualExclusion);   //release buffer
        sem_post(&((consumer *)voidPtr)->beltPtr->empty);

        //exit if consumption is complete
        if(((consumer *)voidPtr)->beltPtr->finishedConsuming){
            return NULL;
        }      
    }
    return NULL;
}