OPENCL= ../opencl
LIBFT=../../libft

all:
	make -C ../opencl lib
	gcc -g main.c -L$(OPENCL) -I$(OPENCL) -L$(LIBFT) -framework OpenCl -lft -lopencl 

run: all
	./a.out

debug: all
	lldb a.out

