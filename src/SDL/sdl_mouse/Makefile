LIBFT=../../../libft/
LIBFT_MODULES=$(addprefix -I $(LIBFT), print string mem array printf/includes gnl .)
NAME=mouse_ttf
SDL_PATH= $(shell cat ../../../include.dep) 
RT:=../../../
MOUSE_INCLUDE = src/brackets/ \
src/maths/ \
src/maths/vec3f/ \
src/objects/ \
src/SDL/sdl_mouse/ \
src/minils/ \
./src/launcher/ \
./src/SDL/ttf/
MOUSE_INCLUDE := $(addprefix -I $(RT), ./ $(MOUSE_INCLUDE)) -I .

all: fclean
	gcc -g -I$(LIBFT)  $(MOUSE_INCLUDE) `sdl2-config --cflags` test.c button.c texture.c media_loader.c texture2.c $(SDL_PATH) $(LIBFT_MODULES) `sdl2-config --libs` -L$(LIBFT) -lSDL2_image -lSDL2_ttf -lft -o $(NAME)

run: all
	./$(NAME)

valgrind: all
	valgrind --leak-check=full ./$(NAME)

fclean:
	rm -rf $(NAME)
