/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #4
* File:        	producer_consumer.h
* Description:  header file for produer/consumer source files
*               • contains struct and function declarations
*************************************************************************************/

#include "belt.h"

/*
* Name:	    frogBite
* Desc:     struct for the crunchy frog bite producer thread
*           • Variable for specified delay
*           • A pointer to the conveyor belt (buffer) in order to keep a reference
*/
struct frogBite{
    int delay;
    conveyorBelt *beltPtr;
};

/*
* Name:	    escargot
* Desc:     struct for the escargot sucker producer thread
*           • Variable for specified delay
*           • A pointer to the conveyor belt (buffer) in order to keep a reference
*/
struct escargot{
    int delay;
    conveyorBelt *beltPtr;
};

/*
* Name:	    consumer
* Desc:     struct for the consumer threads which are distinguishable by the name variable
*           • Variable for specified delay
*           • Counters for the amount of each candy the consumer has consumed
*           • A pointer to the conveyor belt (buffer) in order to keep a reference
*/
struct consumer{
    int delay;
    int frogConsumed = 0;
    int escargotConsumed = 0;
    char *name;
    conveyorBelt *beltPtr;
};

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
void * frogProducer(void * voidPtr);

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
void * escargotProducer(void * voidPtr);

/*
* Name:	    Consumer
* Desc:     consumer function which acts as the consumer thread for the Lucy and Ethel consumers
*           • consumerType is used to distinguish between which thread is which (Lucy or Ethel) and send the correct information
*             to print via io_remove_type as the first parameter
*           • if/else strcmp is used to determine which candy is being consumed, our implementation used a queue<char*> so we are reading
*             the char* at the front of the queue and consuming accordingly.
*           • Two semaphores used for mutual exclusion and to determine if there is anything to consume on the belt (bounded buffer)
* Return:	Exits when the consumption is complete
*/
void * Consumer(void * voidPtr);