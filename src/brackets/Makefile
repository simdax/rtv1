ROOT="../../"

include make.dep
include ../objects/make.dep
include ../maths/make.dep
include ../maths/vec3f/make.dep

all:
	make -C $(LIBFT_PATH)
	gcc -g test_valgrind.c -I. -Iobjects -I../maths \
	-I ../../LSDL2-2.0.8/include -I ../maths/vec3f -I../../ \
	$(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix ../objects/, $(OBJECTS_SRCS)) $(BRACKETS_SRCS) $(MATHS_ABS_SRCS) $(VEC3F_ABS_SRCS) \
	-L$(LIBFT_PATH) -lft -lm

run: all
	./a.out

test: all
	./tests	

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
