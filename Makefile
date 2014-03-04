SRC_DIR = ./src/
OUTPUT_DIR = ./bin/

CC     = g++
CFLAGS = -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib
#LIBS = -lGLEW -lGL -lSDL2 -Wl,-rpath,/usr/local/lib -lm -lSDL2_test -lpthread
LIBS = -lGL -lSDL2

EXE = 

#this make commmand compiles:
#gcc -o main main.c -g -O2 -D_REENTRANT -I/usr/local/include/SDL2   -DHAVE_OPENGL -lSDL2_test -lGL -L/usr/local/lib -lSDL2 -lpthread 

TARGET = gl_nbody

#release:
	#make a bin directory if it does not already exist
	#mkdir -p $(bin)

	#g++ src/main.cpp -lGL -lX11 -lGLU -o bin/main

debug: 
	$(CC) -o $(OUTPUT_DIR)$(TARGET) $(SRC_DIR)main.cpp $(CFLAGS) -g $(LIBS) 
clean: 
	rm -rf bin/*

