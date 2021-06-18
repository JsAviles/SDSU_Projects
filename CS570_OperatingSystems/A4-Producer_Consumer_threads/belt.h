/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #4
* File:        	belt.h
* Description:  header file containing information for bounded buffer "conveyor belt"
*************************************************************************************/

#include <queue>
#include "semaphore.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "io.h"

using namespace std;

/*
* Name:	    conveyorBelt
* Desc:     Data struct used to simulate a bounded buffer (conveyorBelt in this case)
*			for the candy production and consumption problem.
*				• Max candies able to be produced is 100
*				• Max amount of frog candies able to exist on belt is 3
*				• various counters for tracking production progress
*				• boolean flags to indicate when production and consumption are completed
*				• boolean indicator to stop producing frogs if there are currently 3 on the belt
*				• various semaphores used for mutual exclusion, and forindicating whether or not there is space on the convyor belt
*/
struct conveyorBelt{
	int capacity = 10;
	int MAX_FROGS = 3;
	int MAX_Produced = 100;
	int candiesProduced = 0;
    int candiesConsumed = 0;
	int * produced;
	int * consumed;
	int * onBelt;

	ConsumerType *consumer = new ConsumerType;
	ProductType *producer = new ProductType;

    bool finishedProducing = false;
    bool finishedConsuming = false;
	bool frogCapped = false;

	queue<char*> belt;

	sem_t mutualExclusion ; //accessing and releasing the buffer
	sem_t empty ; 			//shows the number of empty slots
	sem_t full ;  			//shows the number of items in the buffer
};