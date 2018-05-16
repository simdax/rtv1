SRCS = opencl.c erasecl.c readcl.c err.c
TEST= test_serieux.c
SRCS:= $(addprefix srcs/, $(SRCS)) 

all : fclean
	gcc -Ilibft -I. -Llibft -lft -framework OpenCL $(SRCS) tests/$(TEST) -o testcl

run : all
	./testcl

fclean :
	rm -rf testcl
