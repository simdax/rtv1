include make.dep

all: fclean
	gcc -g test.c $(SDL_MOUSE_SRCS) `sdl2-config --cflags --libs` -lSDL2_image

run: all
	./a.out

fclean:
	rm -rf a.out
