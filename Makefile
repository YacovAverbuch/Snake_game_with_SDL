
CC = c++
CCFLAGS = -c -Wall -Wextra -std=c++14 -pthread -g
LDFLAGS = -lm

INCLUDE_SDL2_HEADERS = -IDev\SDL2\include -IDev\SDL2_image-2.0.1\include -IDev\SDL2_ttf-2.0.15\include
INCLUDE_PROJECT_HEADERS = -Iproject_headers


LIB_SDL2_PATHS_FOR_LINKER = -LDev\SDL2_image-2.0.1\lib\x64 -LDev\SDL2\lib\x64 -LDev\SDL2_ttf-2.0.15\lib\x64
# when dinamic lib used by the compiler, it create in the executable file a references to the functions it deeds
SDL2_DINAMIC_LIB_NAMES = -lSDL2 -llibpng16-16 -lzlib1 -lSDL2_image -lSDL2_ttf


# STATIC_LIB_SDL2_PATHS = -LDev\onlyLibFiles
# when static lib used by the compiler, it takes the functions it need and past them into the executable file
# SDL2_STATIC_LIB_NAME = -lSDL2 -lSDL2_image





# all .cpp files to compile (no file suffixes)
CLASSES = main SnakeGame SnakeObject TextureManager SideBar Food Obstacle


# Prepare object and source file list using pattern substitution func.
OBJS = $(patsubst %, %.o, $(CLASSES))
SRCS = $(patsubst %, %.c, $(CLASSES))


# "-I<dir>": dir for Include files (header files)
# "-L<dir>": detailed the dir for library
# "-l<library name without 'lib', without '.a'>": the name of the lib (a name of library )
# "-o ...": choose a name for the Output
# "-v": show details about compilation


all: ${OBJS}
	$(CC) ${OBJS} ${LIB_SDL2_PATHS_FOR_LINKER} ${SDL2_DINAMIC_LIB_NAMES} -o SnakeGame

# "$*": the target filename without the file extension.
%.o: %.cpp
	$(CC) $(CCFLAGS) $*.cpp ${INCLUDE_SDL2_HEADERS} ${INCLUDE_PROJECT_HEADERS}


depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)
# DO NOT DELETE


# "echo": get it to the standart output
clean:
	rm -f *.o *.exe
