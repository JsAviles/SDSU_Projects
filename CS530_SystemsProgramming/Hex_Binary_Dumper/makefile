################################################################
# File: makefile for Project #2
# Class: CS530 Fall 2020
# Group Members:  Jesus Aviles,   cssc3040, Red ID: 823931557
#                 Naibi Yilidaer, cssc3054, Red ID: 820217379
#                 Claire Fiorino, cssc3053, Red ID: 821765822
################################################################

CC = g++
FILES = xbd.cpp
EXEC = xbd
OBJECTS = $(FILES:.c=.o)
CFLAGS = -c

$(EXEC):$(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS)
	rm -f *.o

$(OBJECTS):$(OBJECTS)
	$(CC) $(CFLAGS) $(FILES)

clean:
	rm -f *.o $(EXEC) *.lis *.sic

#######################[ EOF: Makefile ]###################