CC=g++
INCLUDES=include
SOURCE_DIR=src
OBJECT_DIR=bin
PROGRAM=squad.out
OPENGL_LIBRARIES=/tools/SITE/lib/Linux64
OPENGL_FLAGS=-lGL -lGLEW -lglut

all: compile link

agent:
	$(CC) -I $(INCLUDES) -o $(OBJECT_DIR)/agent.o -c $(SOURCE_DIR)/agent.cpp

group:
	$(CC) -I $(INCLUDES) -o $(OBJECT_DIR)/group.o -c $(SOURCE_DIR)/group.cpp

main: 
	$(CC) -I $(INCLUDES) -o $(OBJECT_DIR)/main.o -c $(SOURCE_DIR)/main.cpp

compile: agent group main

link:
	$(CC) -L $(OPENGL_LIBRARIES) -o $(PROGRAM) $(OBJECT_DIR)/agent.o $(OBJECT_DIR)/group.o $(OBJECT_DIR)/main.o $(OPENGL_FLAGS)
