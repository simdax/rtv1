SRCS = tests/test2.c opencl.c erasecl.c readcl.c err.c

all : fclean
	gcc -Ilibft -I. -Llibft -lft -framework OpenCL $(SRCS) -o testcl

run : all
	./testcl

fclean :
	rm -rf testcl
