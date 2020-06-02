
OBJS = learning.cpp LTexture.cpp
OBJ_NAME = learning

CC = g++
INCLUDE_PATHS = -IC:\mingw-dev-lib\include\SDL2
LIBRARY_PATHS = -LC:\mingw-dev-lib\lib
COMPILER_FLAGS = -Wall -Wextra -pedantic
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)