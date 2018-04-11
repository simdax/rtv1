include make.dep
LIBFT=./libft
NAME=mouse_ttf

all: fclean
	gcc -g -I$(LIBFT) test.c $(SDL_MOUSE_SRCS) `sdl2-config --cflags --libs` -L$(LIBFT) -lSDL2_image -lSDL2_ttf -lft -o $(NAME)

run: all
	./$(NAME)

valgrind: all
	valgrind --leak-check=full ./$(NAME)

fclean:
	rm -rf $(NAME)
