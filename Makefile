SRC_DIR = ./src/
OUTPUT_DIR = ./bin/

CC     = g++
CFLAGS = -I/usr/local/include/SDL2 -DHAVE_OPENGL  
LIBS = -lSDL2 -Wl,-rpath,/usr/local/lib -L/usr/local/lib 
EXE = 

TARGETS = \
	gl_nbody

release:
	#make a bin directory if it does not already exist
	#mkdir -p $(bin)

	g++ src/main.cpp -lGL -lX11 -lGLU -o bin/main

debug: 
	$(CC) -o $(OUTPUT_DIR)/$@ $(CFLAGS) -g $(LIBS) 
clean: 
	rm -rf bin/*

