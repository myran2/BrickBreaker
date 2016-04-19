#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard src/*.cpp)


#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -std=c++11 $(shell sdl2-config --cflags) -I./src

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = BrickBreaker

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
