include make.dep
include ../objects/make.dep

all:
	make -C $(LIBFT_PATH)
	gcc -g test_valgrind.c ../maths/resolveQuadratics.c -I. -Iobjects -I../maths \
	-I ../../LSDL2-2.0.8/include -I ../objects/vec3f -I../../ \
	$(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix ../objects/, $(OBJECTS_SRCS)) $(BRACKETS_SRCS) \
	-L$(LIBFT_PATH) -lft -lm

run: all
	./a.out

test: all
	./tests	

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
