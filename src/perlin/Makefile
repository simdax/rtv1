OPENCL= ../opencl
LIBFT=../../libft
SRCS = main.c perlin.c image.c perlin_image.c $(LIBFT)/mem/ft_memalloc.c
INCLUDES = -I$(OPENCL) -I$(LIBFT) -I$(LIBFT)/mem
LINKS = -L$(OPENCL) -L$(LIBFT) -framework OpenCl -lft -lopencl

all:
	make -C ../opencl lib
	make -C $(LIBFT)
	gcc -g $(SRCS) $(INCLUDES) $(LINKS)

run: all
	./a.out
	open ./perlin.ppm

debug: all
	lldb a.out
