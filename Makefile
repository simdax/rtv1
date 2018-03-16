SRCS=main.c sdl.c sphere.c transparency.c diffuse.c trace.c
SRCS:=$(addprefix src/, $(SRCS))
LINK=-LSDL2-2.0.8/build/ -lSDL2 -lm -Llibft -lft
HEADERS=rtv1.h srcs/objects/sphere.h vec3f/vec3f.h
INCLUDE=. vec3f SDL2-2.0.8/include libft
INCLUDE:=$(addprefix -I, $(INCLUDE))
COMPILE=gcc -g -O3
NAME=rtv1

include src/brackets/make.dep
include src/objects/make.dep

all:
	make compile
	./a.out

compile: libft $(SRCS) $(HEADERS) 
	$(COMPILE) $(LINK) $(INCLUDE) $(SRCS) -o $(NAME)

libft:
	make -C libft
