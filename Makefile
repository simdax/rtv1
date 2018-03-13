SRCS=main.c sdl.c sphere.c transparency.c diffuse.c trace.c parse.c
SRCS:=$(addprefix src/, $(SRCS))
SRCS += vec3f/vec3f.c
LINK=-LSDL2-2.0.8/build/ -lSDL2 -lm -Llibft -lft
HEADERS=rtv1.h vec3f/vec3f.h
INCLUDE=. vec3f SDL2-2.0.8/include libft
INCLUDE:=$(addprefix -I, $(INCLUDE))
COMPILE=gcc -g -O3

all:
	make compile
	./a.out

compile: libft $(SRCS) $(HEADERS) 
	$(COMPILE) $(LINK) $(INCLUDE) $(SRCS)

libft:
	make -C libft
