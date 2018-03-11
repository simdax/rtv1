SRCS=main.c sphere.c trace.c vec3f/vec3f.c
INCLUDE=vec3f
COMPILE=gcc -g -O3

all:
	make compile
	./a.out

compile:
	$(COMPILE) -lm -I$(INCLUDE) $(SRCS)
