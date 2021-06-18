##############################################################
# Name:        	Jesus Aviles, cssc3404, RED ID: 823931557
#				Dao Vo      , cssc3459, RED ID: 820901504
# Class:        CS570 Spring 2021
# Assignment:   Assignment #1
# File:        	makefile
# Description:  makefile for compiling myls.cpp source code
###############################################################

CC = g++
CFLAGS = -c
TARGET = myls

all: $(TARGET)

$(TARGET): myls.o
	$(CC) myls.o -o $(TARGET)
	rm -f *.o
myls.o: myls.cpp
	$(CC) $(CFLAGS) myls.cpp

clean:
	rm -f core *.o $(TARGET)

