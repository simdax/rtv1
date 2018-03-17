include make.dep
include ../objects/make.dep

all:
	make -C $(LIBFT_PATH)
	gcc -g test_valgrind.c -I. $(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix ../objects/, $(OBJECTS_SRCS)) $(BRACKETS_SRCS) \
	-L$(LIBFT_PATH) -lft -lm

run: all
	./a.out

test: all
	./tests	

test_valgrind: all
	valgrind --leak-check=full ./a.out
