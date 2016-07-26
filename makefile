CC=g++
INCLUDES=include
SOURCE_DIR=src
OBJECT_DIR=bin
PROGRAM=squad.out


compile:
	$(CC) -I $(INCLUDES) -o $(OBJECT_DIR)/agent.o -c $(SOURCE_DIR)/agent.cpp
	$(CC) -I $(INCLUDES) -o $(OBJECT_DIR)/group.o -c $(SOURCE_DIR)/group.cpp

link:
	$(CC) -o $(PROGRAM) 
