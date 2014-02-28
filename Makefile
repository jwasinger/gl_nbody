release:
	#make a bin directory if it does not already exist
	#mkdir -p $(bin)

	g++ src/main.cpp -lGL -lX11 -lGLU -o bin/main

debug: 
	g++ -c src/main.cpp -g	
clean: 
	rm bin/main

main.o:
