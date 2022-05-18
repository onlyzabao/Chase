OBJS = Texture.cpp Painter.cpp Mixer.cpp Button.cpp GameUI.cpp

CC = g++

INCLUDE_PATHS = -I..\include\SDL2

LIBRARY_PATHS = -L..\lib

# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
# COMPILER_FLAGS = -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	