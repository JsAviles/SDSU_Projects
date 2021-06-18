################################################################
# File: makefile for Assignment #4
# Class: CS570 Spring 2021
# Group Members:  Jesus Aviles, cssc3040, Red ID: 823931557
#                 Dao Vo      , cssc3020, Red ID: 820901504
#       
################################################################

CC = g++
FILES = mizzo.cpp io.c producer.cpp consumer.cpp
EXEC = mizzo
OBJECTS = $(FILES:.c=.o)
CFLAGS = -c

$(EXEC):$(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -g -lpthread -lrt
	rm -f *.o

$(OBJECTS):$(OBJECTS)
	$(CC) $(CFLAGS) $(FILES)

clean:
	rm -f *.o $(EXEC)

#######################[ EOF: Makefile ]###################