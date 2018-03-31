ROOT := $(realpath .)
SRCS=main.c thread.c
SRCS_RT=transparency.c diffuse.c trace.c
SRCS:=$(addprefix src/, $(SRCS))
SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
SRCS+=$(SRCS_RT)
LINK=-lm -Llibft -lft -lpthread `sdl2-config --libs`
HEADERS=rtv1.h 
INCLUDE=. src/brackets/ src/maths/ src/objects/vec3f src/objects/ \
		src/SDL src/SDL/sdl_mouse libft
INCLUDE:=$(addprefix -I, $(INCLUDE)) `sdl2-config --cflags`
COMPILE=gcc -g #-O3
NAME=rtv1

include src/brackets/make.dep
include src/maths/make.dep
include src/objects/make.dep
include src/SDL/make.dep

VENDOR = $(addprefix src/brackets/, $(BRACKETS_SRCS)) \
	$(addprefix src/objects/, $(OBJECTS_SRCS)) \
	$(addprefix src/maths/, $(MATHS_SRCS)) \
	$(SDL_SRCS)

OBJS=$(SRCS:%.c=%.o)
OBJS+=$(VENDOR:%.c=%.o)

all:
	make -C ./libft
	@echo "gros RTV1 en construction in"
	@make compile

%.o : %.c
	$(COMPILE) $(INCLUDE) -c $< -o $@ 

compile: $(SRCS) $(HEADERS) 
	$(COMPILE) $(INCLUDE) $(SRCS) $(VENDOR) $(LINK) -o $(NAME)

debug: all
	gdb --fullname --args ~/rtv1/rtv1 configs/config2 

valgrind: all
	valgrind --leak-check=full ./$(NAME)

config1: all
	@./$(NAME) configs/config

config2: all
	@./$(NAME) configs/config2

config3: all
	@./$(NAME) configs/config3

config4: all
	@./$(NAME) configs/config4

config5: all
	@./$(NAME) configs/config5
