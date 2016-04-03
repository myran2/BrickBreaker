default:
	tar xf ubuntu-14.04_amd64_lib.tar

	g++ -Wall -g -Iinclude/SDL2 -Iinclude -std=c++11 -c src/BrickBreaker.cpp -o BrickBreaker.o
	g++ -Wall -g -Iinclude/SDL2 -Iinclude -std=c++11 -c src/Window.cpp -o Window.o

	g++ -Llib -Wl,-rpath,lib BrickBreaker.o Window.o  -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread -Wl,--no-undefined -lm -ldl -lpthread -lrt -o BrickBreaker

clean:
	rm -f *.o *~