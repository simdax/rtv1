include make.dep
include ../objects/make.dep

all:
	gcc -g $(VENDOR) $(addprefix ../objects/, $(OBJECTS_SRCS)) $(BRACKETS_SRCS) \
		-L$(LIBFT_PATH) $(BRACKETS_INCLUDE) -lft

run: all
	./a.out

test: all
	./tests	
