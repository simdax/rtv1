SRCS=main.c sphere.c diffuse.c trace2.c vec3f/vec3f.c
HEADERS=rtv1.h vec3f/vec3f.h
INCLUDE=vec3f
COMPILE=gcc -g -O3

all:
	make compile
	./a.out

compile: $(SRCS) $(HEADERS)
	$(COMPILE) -lm -I$(INCLUDE) $(SRCS)
