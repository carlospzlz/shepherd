CC=g++
INCLUDES=include
SOURCE_DIR=src
OBJECT_DIR=bin
PROGRAM=shepherd.out
LIBRARIES=/usr/lib64
COMPILING_FLAGS=-g
LINKING_FLAGS=-lGL -lGLEW -lglfw

all: compile link

agent:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/agent.o -c $(SOURCE_DIR)/agent.cpp

prey:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/prey.o -c $(SOURCE_DIR)/prey.cpp

predator:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/predator.o -c $(SOURCE_DIR)/predator.cpp

environment:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/environment.o -c $(SOURCE_DIR)/environment.cpp

world:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/world.o -c $(SOURCE_DIR)/world.cpp

renderer:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/renderer.o -c $(SOURCE_DIR)/renderer.cpp

main: 
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/main.o -c $(SOURCE_DIR)/main.cpp

compile: agent environment world renderer main

link:
	$(CC) -L $(LIBRARIES) -o $(PROGRAM) $(OBJECT_DIR)/agent.o $(OBJECT_DIR)/world.o $(OBJECT_DIR)/renderer.o $(OBJECT_DIR)/main.o $(LINKING_FLAGS)
