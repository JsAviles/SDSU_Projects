################################################################
# File: makefile for Project #3
# Class: CS530 Fall 2020
# Group Members:  Jesus Aviles, cssc3040, Red ID: 823931557
#                 Dao Vo      , cssc3020, Red ID: 820901504
#       
################################################################

CC = g++
FILES = Parser.cpp
EXEC = parser
OBJECTS = $(FILES:.c=.o)
CFLAGS = -c

$(EXEC):$(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
	rm -f *.o

$(OBJECTS):$(OBJECTS)
	$(CC) $(CFLAGS) $(FILES)

clean:
	rm -f *.o $(EXEC) parsed.txt sedparsed.txt

#######################[ EOF: Makefile ]###################