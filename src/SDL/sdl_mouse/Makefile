LIBFT=../../../libft/
LIBFT_MODULES=$(addprefix -I $(LIBFT), string mem array printf/includes gnl .)
NAME=mouse_ttf
SDL_PATH= $(shell cat ../../../include.dep)

all: fclean
	$(MAKE) -C ../../../ SDL2
	gcc -g -I$(LIBFT) test.c button.c texture.c media_loader.c texture2.c $(SDL_PATH) $(LIBFT_MODULES) -L$(LIBFT) -lft -o $(NAME)

run: all
	./$(NAME)

valgrind: all
	valgrind --leak-check=full ./$(NAME)

fclean:
	rm -rf $(NAME)
