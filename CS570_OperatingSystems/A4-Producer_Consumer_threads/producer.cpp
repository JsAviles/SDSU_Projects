/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #4
* File:        	producer.cpp
* Description:  Source code for "Producer functionality of producer/consumer problem"
*************************************************************************************/

#include "producer_consumer.h"

/*
* Name:	    frogProducer
* Desc:     Production function which acts at the producer thread for creating crunch frog bites on the conveyor belt.
*           • Implementation of semaphores to ensure mutual exclusion when accessing the buffer (conveyor belt)
*           • Logical implementation to signal when production is complete
*           • nanosleep implementation to put the thread to sleep/delay production with the user specified input
*               • otherwise the default delay is 0ms
*           • additional logic to ensure that only a maximum of 3 frogbites exist in the buffer at any given time
*           • Two semaphores used for mutual exclusion and to determine if there is any space to produce a candy on the belt (bounded buffer)
* Return:	Exits the thread when production is complete
*/
void * frogProducer(void * voidPtr){

	//Set up delay based on Dr. Roch FAQ specifications
    struct timespec	SleepTime;
	SleepTime.tv_sec = ((frogBite *)voidPtr)->delay / 1000;	 //# secs
	SleepTime.tv_nsec = (((frogBite *)voidPtr)->delay % 1000) * 1000000; //# nanosecs

    //char pointer used as the type being added to the queue<char*>
    char * frog = new char[2];
    frog[0] = 'f';
    frog[1] = '\0';
    
    while(!((frogBite *)voidPtr)->beltPtr->finishedProducing){

        //sleep for designated delay time (0 if not specified)
        nanosleep(&SleepTime, NULL);

        //check if there are 3 frog bites in the buffer, if not then continue production of frog bites
        if(!((frogBite *)voidPtr)->beltPtr->frogCapped && !((frogBite *)voidPtr)->beltPtr->finishedProducing){
            sem_wait(&((frogBite *)voidPtr)->beltPtr->empty);             //one fewer slot or wait
            sem_wait(&((frogBite *)voidPtr)->beltPtr->mutualExclusion);   //get access to buffer

            //push a frog onto the queue (bounded buffer/conveyor belt)
            ((frogBite *)voidPtr)->beltPtr->belt.push(frog);
            ((frogBite *)voidPtr)->beltPtr->candiesProduced += 1;
            ((frogBite *)voidPtr)->beltPtr->produced[0] += 1;
            ((frogBite *)voidPtr)->beltPtr->onBelt[0] += 1;

            //output production based on professors provided output scheme
            io_add_type(1, ((frogBite *)voidPtr)->beltPtr->onBelt, ((frogBite *)voidPtr)->beltPtr->produced);
            cout << flush;

            if(((frogBite *)voidPtr)->beltPtr->onBelt[0] == ((frogBite *)voidPtr)->beltPtr->MAX_FROGS){
                ((frogBite *)voidPtr)->beltPtr->frogCapped = true;
            }
            //check to see if 100 candies were produced and end production
            if(((frogBite *)voidPtr)->beltPtr->candiesProduced == ((frogBite *)voidPtr)->beltPtr->MAX_Produced){
                ((frogBite *)voidPtr)->beltPtr->finishedProducing = true;
            }

            sem_post(&((frogBite *)voidPtr)->beltPtr->mutualExclusion);   //release buffer
            sem_post(&((frogBite *)voidPtr)->beltPtr->full);              //one more slot used

            //if production is over, exit thread
            if(((frogBite *)voidPtr)->beltPtr->finishedProducing){
                return NULL;
            }
        }
    }
    return NULL;
}

/*
* Name:	    escargotProducer
* Desc:     Production function which acts at the producer thread for creating escargot suckers on the conveyor belt.
*           • Implementation of semaphores to ensure mutual exclusion when accessing the buffer (conveyor belt)
*           • Logical implementation to signal when production is complete
*           • nanosleep implementation to put the thread to sleep/delay production with the user specified input
*               • otherwise the default delay is 0ms
*           • Two semaphores used for mutual exclusion and to determine if there is any space to produce a candy on the belt (bounded buffer)
* Return:	Exits the thread when production is complete
*/
void * escargotProducer(void * voidPtr){

    //char pointer used as the type being added to the queue<char*>
	char * eS = new char[2];
    eS[0] = 'e';
    eS[1] = '\0';

	//Set up delay based on Dr. Roch FAQ specifications
    struct timespec	SleepTime;
	SleepTime.tv_sec = ((escargot *)voidPtr)->delay / 1000;	 //# secs
	SleepTime.tv_nsec = (((escargot *)voidPtr)->delay % 1000) * 1000000; //# nanosecs

    while(!((escargot *)voidPtr)->beltPtr->finishedProducing){

        //sleep for designated delay time (0 if not specified)
        nanosleep(&SleepTime, NULL);

        //check to see if 100 candies were produced and end production
        sem_wait(&((escargot *)voidPtr)->beltPtr->empty);             //one fewer slot or wait
        sem_wait(&((escargot *)voidPtr)->beltPtr->mutualExclusion);   //get access to buffer

        //push an escargot sucker onto the queue (bounded buffer/conveyor belt)
        if(!((escargot *)voidPtr)->beltPtr->finishedProducing){
            ((escargot *)voidPtr)->beltPtr->belt.push(eS);
            ((escargot *)voidPtr)->beltPtr->candiesProduced += 1;
            ((escargot *)voidPtr)->beltPtr->produced[1] += 1;
            ((escargot *)voidPtr)->beltPtr->onBelt[1] += 1;

            //output production based on professors provided output scheme
            io_add_type(1, ((escargot *)voidPtr)->beltPtr->onBelt, ((escargot *)voidPtr)->beltPtr->produced);
            cout <<flush;
        }

        if(((escargot *)voidPtr)->beltPtr->candiesProduced == ((escargot *)voidPtr)->beltPtr->MAX_Produced){
            ((escargot *)voidPtr)->beltPtr->finishedProducing = true;
        }
        sem_post(&((escargot *)voidPtr)->beltPtr->mutualExclusion);   //release buffer
        sem_post(&((escargot *)voidPtr)->beltPtr->full);              //one more slot used
        
        //if production is over, exit thread
        if(((escargot *)voidPtr)->beltPtr->finishedProducing){
                return NULL;
            }
    }
    return NULL;
}