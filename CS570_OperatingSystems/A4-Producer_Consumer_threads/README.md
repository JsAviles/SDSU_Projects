<h1 align="center">Assignment #4 - Producer/Consumer Threads (Semaphores)</h1>

<div align="center">Operating Systems - Spring 2021</div>

# Table of Contents

1. [About](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A4-Producer_Consumer_threads#about)
2. [Functionality](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A4-Producer_Consumer_threads#Functionality)
3. [Sample Output](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A4-Producer_Consumer_threads#Sample-output)
4. [Contributors](https://github.com/JsAviles/SDSU_Projects/tree/main/CS570_OperatingSystems/A4-Producer_Consumer_threads#Contributors)

## About

This project simulates a candy factory conveyor belt with 2 workers, Lucy and Ethel (as seen in I love Lucy). The factory "Mizzo" produces two types of candy: crunchy frog bites and everlasting escargot suckers. The conveyor belt (acting as our bounded buffer) may only hold up to 10 candies at any given time with a restriction of 3 frog bites at most. Candies are boxed in the order they are produced. To accomplish the producer/consumer simulation problem, we will use 4 threads, a bounded buffer, and the implementation of semaphors with critical sections.

## Functionality

### To get started with compilation and execution on the command line...

* Type **make** as shown below

        $ make

* Then use the executable name **mizzo**

        $ mizzo "see Optional Arguments"
    
* Optional Arguments:

    * **-E N** - Specifies the number of milliseconds 'N' that the Ethel Consumer takes to box a candy, regardless of candy type.
    * **-L N** - Specifies the number of milliseconds 'N' that the Lucy Consumer takes to box a candy, regardless of candy type.
    * **-f N** - Specifies the number of milliseconds 'N' required to produce a single crunchy frog bite candy.
    * **-e N** - Specifies the number of milliseconds 'N' required to produce a single everlasting escargot sucker.
    * If no argument is given for any one of the above flags or none at all, then by default, the threads will incur no delay

* Each time the conveyor belt is mutated, the production is displayed showing the current state of the conveyor belt and the statistics candy production/consumption.

* Once 100 candies have been produced and consumed, a summary report is displayed showing each threads production or consumption count along with the elapsed time of the conveyor belts run-time.

## Sample output

    $ mizzo -f 5 -e 15 -E 35 -L 20

![alt text](https://i.gyazo.com/36be930a952addf92ac115d099da2e18.png)

## Contributors

* Jesus Sebastian Aviles

    ![alt text](https://i.gyazo.com/30c872a61a8257508866840b44592530.png)

    Contact info:

    * sebastian_aviles@yahoo.com

    * [Linkedin](https://www.linkedin.com/in/sebastian-aviles-215b3471/)

* Dao Vo

    * [Linkedin](https://www.linkedin.com/in/dao-vo-07673b1b8/)
