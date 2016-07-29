CC=g++
INCLUDES=include
SOURCE_DIR=src
OBJECT_DIR=bin
PROGRAM=flock.out
LIBRARIES=/usr/lib64
COMPILING_FLAGS=-g
LINKING_FLAGS=-lGL -lGLEW -lglfw

all: compile link

vec2:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/vec2.o -c $(SOURCE_DIR)/vec2.cpp 

agent:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/agent.o -c $(SOURCE_DIR)/agent.cpp

world:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/world.o -c $(SOURCE_DIR)/world.cpp

renderer:
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/renderer.o -c $(SOURCE_DIR)/renderer.cpp

main: 
	$(CC) $(COMPILING_FLAGS) -I $(INCLUDES) -o $(OBJECT_DIR)/main.o -c $(SOURCE_DIR)/main.cpp

compile: vec2 agent world renderer main

link:
	$(CC) -L $(LIBRARIES) -o $(PROGRAM) $(OBJECT_DIR)/vec2.o $(OBJECT_DIR)/agent.o $(OBJECT_DIR)/world.o $(OBJECT_DIR)/renderer.o $(OBJECT_DIR)/main.o $(LINKING_FLAGS)
