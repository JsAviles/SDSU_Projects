/*************************************************************************************
* Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
*    			Dao Vo      , cssc3459, RED ID: 820901504
* Class:        CS570 Spring 2021
* Assignment:   Assignment #4
* File:        	mizzo.cpp
* Description:  main/Driver source file that implements producer/consumer problem
*************************************************************************************/

#include "producer_consumer.h"

/*************************************************************************************
*																					 *
*									MAIN											 *
*																					 *
*************************************************************************************/
int main(int argc, char **argv){
	
	//getopt flags and variables
	int opt;
	int argCtr = 0; //helper to read in user inputs
	bool flag_f = false;
	bool flag_e = false;
	bool flag_E = false; 
	bool flag_L = false;

	//temp variables to capture user input delay (otherwise kept 0)
	int make_frog = 0;
	int make_escargot = 0;
	int store_Ethel = 0;
	int store_Lucy = 0;
	
	//use getopt to factor in user flags
	while ( (opt = getopt(argc, argv, "f:e:E:L:")) != -1){
		switch (opt) {
		case 'f': //
			make_frog = atoi(optarg); //speed to make 1 frog
			flag_f = true;
			argCtr += 2;
			break;
		case 'e': 
			make_escargot = atoi(optarg);// optarg contains the output method…
			flag_e = true;
			argCtr += 2;
			break;
		case 'E': //to specify output type
			store_Ethel = atoi(optarg);// optarg contains the output method…
			flag_E = true;
			argCtr += 2;
			break;
		case 'L': //to specify output type
			store_Lucy = atoi(optarg);// optarg contains the output method…
			flag_L = true;
			argCtr += 2;
			break;
		default:
			exit(EXIT_FAILURE); //graceful exit if flag does not match 'f', 'e', 'E' or 'L'
		}
	}

	//Instantiate bounded buffer (conveyor Belt) and allocate memory for it's various components
	conveyorBelt * cBelt = new conveyorBelt;
	cBelt->produced = new int[2];
	cBelt->produced[0] = 0;
	cBelt->produced[1] = 0;
	cBelt->consumed = new int[2];
	cBelt->consumed[0] = 0;
	cBelt->consumed[1] = 0;
	cBelt->onBelt = new int[2];
	cBelt->onBelt[0] = 0;
	cBelt->onBelt[1] = 0;
	
	//initiate semaphores used in the production/consumption
    sem_init(&cBelt->mutualExclusion, 0, 1);
    sem_init(&cBelt->empty, 0, 10);
    sem_init(&cBelt->full, 0, 0);

	//instantiate producers/consumers for use
    frogBite * f = new frogBite;
    escargot * e = new escargot;
    consumer *L = new consumer;
    consumer *E = new consumer;

	//Initialize delay variables for producers/consumers based on user input (otherwise 0)
	f->delay = make_frog;
	e->delay = make_escargot;
	L->delay = store_Lucy;
	E->delay = store_Ethel;

	//link producer/consumer pointers to the convery belt (bounded buffer)
    f->beltPtr = cBelt;
    e->beltPtr = cBelt;
    L->beltPtr = cBelt;
	E->beltPtr = cBelt;
	
	//initialize the name variables of the consumers for use in the consumer function
    L->name = new char[5];
    L->name[0] = 'L';
    L->name[1] = 'u';
    L->name[2] = 'c';
    L->name[3] = 'y';
    L->name[4] = '\0';
    E->name = new char[6];
    E->name[0] = 'E';
    E->name[1] = 't';
    E->name[2] = 'h';
    E->name[3] = 'e';
    E->name[4] = 'l';
    E->name[5] = '\0';

	//instantiate our producer/consumer threads
    pthread_t frogThread;
    pthread_t escargotThread;
    pthread_t Lucy;
    pthread_t Ethel;

	//begin the producer/consumer conveyor belt procedure
    pthread_create(&frogThread, NULL, &frogProducer, (void *) f);
    pthread_create(&escargotThread, NULL, &escargotProducer, (void *) e);
    pthread_create(&Lucy, NULL, &Consumer, (void *) L);
    pthread_create(&Ethel, NULL, &Consumer, (void *) E);

	//barrier to ensure when production is finished which then initializes some statistical variables used for reporting production
    while(true){
        if (cBelt->finishedConsuming && cBelt->finishedProducing){
			pthread_cancel(frogThread);
			pthread_cancel(escargotThread);
			pthread_cancel(Lucy);
			pthread_cancel(Ethel);
			int produced [] = {(L->frogConsumed + E->frogConsumed),(L->escargotConsumed + E->escargotConsumed)};
			int *consumed [2] = {};
			consumed[0] = new int[2];
			consumed[1] = new int[2];
			consumed[0][0] = L->frogConsumed;
			consumed[0][1] = L->escargotConsumed;
			consumed[1][0] = E->frogConsumed;
			consumed[1][1] = E->escargotConsumed;
			io_production_report(produced, consumed);
            break;
        }
    }
}