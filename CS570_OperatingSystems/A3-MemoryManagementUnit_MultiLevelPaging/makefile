################################################################
# File: makefile for Assignment #3
# Class: CS570 Spring 2021
# Group Members:  Jesus Aviles, cssc3040, Red ID: 823931557
#                 Dao Vo      , cssc3020, Red ID: 820901504
#       
################################################################

CC = g++
FILES = pagetable.cpp byu_tracereader.c helpers.cpp
EXEC = pagetable
OBJECTS = $(FILES:.c=.o)
CFLAGS = -c

$(EXEC):$(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -lpthread
	rm -f *.o

$(OBJECTS):$(OBJECTS)
	$(CC) $(CFLAGS) $(FILES)

clean:
	rm -f *.o $(EXEC)

#######################[ EOF: Makefile ]###################