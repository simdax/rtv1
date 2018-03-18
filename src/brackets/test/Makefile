OBJ_PATH = ../../objects

include ../make.dep
include $(OBJ_PATH)/make.dep

all:
	make -C ../$(LIBFT_PATH)
	gcc -g test_valgrind.c -I. -I$(OBJ_PATH) ../$(BRACKETS_INCLUDE) $(VENDOR) \
	$(addprefix $(OBJ_PATH)/, $(OBJECTS_SRCS)) ../$(BRACKETS_SRCS) \
	-L../$(LIBFT_PATH) -lft -lm

run: all
	./a.out

test: all
	./tests	

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
