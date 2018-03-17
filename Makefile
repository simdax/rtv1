SRCS=main.c sdl.c transparency.c diffuse2.c trace.false2.c
SRCS:=$(addprefix src/, $(SRCS))
LINK=-LSDL2-2.0.8/build/ -lSDL2 -lm -Llibft -lft
HEADERS=rtv1.h 
INCLUDE=. src/brackets/ src/objects/vec3f src/objects/ SDL2-2.0.8/include libft
INCLUDE:=$(addprefix -I, $(INCLUDE))
COMPILE=gcc -g
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
	@./$(NAME)

%.o : %.c
	$(COMPILE) $(INCLUDE) -c $< -o $@ 

compile: libft $(SRCS) $(HEADERS) 
	$(COMPILE) $(INCLUDE) $(SRCS) $(VENDOR) $(LINK) -o $(NAME)

libft:
	make -C libft
