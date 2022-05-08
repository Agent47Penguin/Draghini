#CC specifies which compiler we're using
CC = g++

#OBJS specifies which files to compile as part of the project
OBJS = src/Main.cpp

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:/ProgrammingLibraries/SDL2-mingw/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:/ProgrammingLibraries/SDL2-mingw/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = #-w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = target/Main.exe

#This is the target that compiles our executable
build:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)