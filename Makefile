SRCS=main.c sdl.c thread.c
SRCS_RT=transparency.c diffuse.c trace.c
SRCS:=$(addprefix src/, $(SRCS))
SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
SRCS+=$(SRCS_RT)
LINK=-LSDL2-2.0.8/build/ -lSDL2 -lm -Llibft -lft -lpthread
HEADERS=rtv1.h 
INCLUDE=. src/brackets/ src/objects/vec3f src/objects/ SDL2-2.0.8/include libft
INCLUDE:=$(addprefix -I, $(INCLUDE))
COMPILE=gcc -g #-O3
NAME=rtv1

include src/brackets/make.dep
include src/objects/make.dep

VENDOR = $(addprefix src/brackets/, $(BRACKETS_SRCS)) \
	$(addprefix src/objects/, $(OBJECTS_SRCS))
OBJS=$(SRCS:%.c=%.o)
OBJS+=$(VENDOR:%.c=%.o)

all:
	@echo "gros RTV1 en construction in"
	@make compile

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

%.o : %.c
	$(COMPILE) $(INCLUDE) -c $< -o $@ 

compile: libft $(SRCS) $(HEADERS) 
	$(COMPILE) $(INCLUDE) $(SRCS) $(VENDOR) $(LINK) -o $(NAME)

libft:
	make -C libft

debug: all
	gdb --fullname --args ~/rtv1/rtv1 configs/config2 

valgrind: all
	valgrind --leak-check=full ./$(NAME)
