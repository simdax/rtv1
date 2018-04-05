NAME = FontTest 

all:
	g++ -g `sdl2-config --libs --cflags` ttf.cpp -std=c++1y -lSDL2 -lSDL2_ttf -o FontTest && ./FontTest	

run: all
	./$(NAME)
