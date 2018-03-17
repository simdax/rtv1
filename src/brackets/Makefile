include make.dep
include ../objects/make.dep

all:
	gcc -g utils.c -I. $(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix ../objects/, $(OBJECTS_SRCS)) $(BRACKETS_SRCS) \
	-L$(LIBFT_PATH) -lft -lm

run: all
	./a.out

test: all
	./tests	
