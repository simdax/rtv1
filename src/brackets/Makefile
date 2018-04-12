ROOT="../../"

include make.dep
include ../objects/make.dep
include ../maths/make.dep
include ../maths/vec3f/make.dep

TEST="test/valgrind.c"

all:
	make -C $(LIBFT_PATH)
	gcc -g $(TEST) -I. -Iobjects -I../maths \
	-I ../../LSDL2-2.0.8/include -I ../maths/vec3f -I../../ \
	$(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix ../objects/, $(OBJECTS_SRCS)) $(LOCAL_INCLUDES) $(MATHS_ABS_SRCS) $(VEC3F_ABS_SRCS) \
	-L$(LIBFT_PATH) -lft -lm

run: all
	./a.out

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
