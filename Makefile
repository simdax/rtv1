SRCS=main.c sdl.c sphere.c transparency.c diffuse.c trace.c
SRCS:=$(addprefix src/, $(SRCS))
SRCS += vec3f/vec3f.c
LINK=-LSDL2-2.0.8/build/ -lSDL2 -lm
HEADERS=rtv1.h vec3f/vec3f.h
INCLUDE=. vec3f SDL2-2.0.8/include
INCLUDE:=$(addprefix -I, $(INCLUDE))
COMPILE=gcc -g -O3

all:
	make compile
	./a.out

compile: $(SRCS) $(HEADERS)
	$(COMPILE) $(LINK) $(INCLUDE) $(SRCS)
