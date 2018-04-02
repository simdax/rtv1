include make.dep
LIBFT=./libft

all: fclean
	gcc -g -I$(LIBFT) test.c $(SDL_MOUSE_SRCS) `sdl2-config --cflags --libs` -L$(LIBFT) -lSDL2_image -lSDL2_ttf -lft

run: all
	./a.out

valgrind: all
	valgrind --leak-check=full ./a.out

fclean:
	rm -rf a.out
