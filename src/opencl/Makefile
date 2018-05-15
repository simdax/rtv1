all : fclean
	gcc -Llibft -lft -framework OpenCL test.c opencl.c erasecl.c readcl.c -o testcl

fclean :
	rm -rf testcl
