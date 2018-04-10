SRCS=main.c sdl.c thread.c
SRCS_RT=fx.c diffuse.c trace.c
SRCS:=$(addprefix src/, $(SRCS))
SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
SRCS+=$(SRCS_RT)
LINK=`sdl2-config --libs` -lm -Llibft -lft -lpthread #LSDL2-2.0.8/build/.libs -lSDL2
HEADERS=rtv1.h 
INCLUDE=. src/brackets/ src/maths/ src/maths/vec3f src/objects/ libft 
INCLUDE:=$(addprefix -I, $(INCLUDE)) $(shell sdl2-config --cflags)
COMPILE=gcc -g #-O3
NAME=rtv1

include src/brackets/make.dep
include src/maths/make.dep
include src/maths/vec3f/make.dep
include src/objects/make.dep

VENDOR = $(addprefix src/brackets/, $(BRACKETS_SRCS)) \
	$(addprefix src/objects/, $(OBJECTS_SRCS)) \
	$(addprefix src/maths/, $(MATHS_SRCS)) \
	$(addprefix src/maths/vec3f/, $(VEC3F_SRCS))	
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

config6: all
	@./$(NAME) configs/config6

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
