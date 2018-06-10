NAME= libopencl.a
LIBFT=../../libft
LIBFT_SRCS:= ft_memalloc.c ft_strdel.c get_next_line.c
#LIBFT_SRCS:= $(addprefix $(LIBFT)/, $(LIBFT_SRCS))
SRCS= opencl.c erasecl.c readcl.c err.c create_tests.c create_program.c
#SRCS:= $(addprefix srcs/, $(SRCS))
SRCS:= $(SRCS) #$(LIBFT_SRCS)
OBJS=$(SRCS:%.c=%.o)
TEST= tests/test_intersect.c
INCLUDES := . ./libft ../objects ../maths/vec3f
INCLUDES := $(addprefix -I, $(INCLUDES))
CL_FILES= ../maths/vec3f/vec3f.cl ../maths/maths.cl ../objects/sphere.cl
CL_FINAL= all.cl

vpath %.c srcs
#vpath %.c $(LIBFT)/mem:$(LIBFT)/string:$(LIBFT)/gnl
vpath %.o objs

all : lib $(NAME)
# @echo "\e[31m compilation de $(TEST) \e[0m"
	@gcc -g $(INCLUDES) -Llibft -lft -framework OpenCL $(NAME) $(TEST) -o testcl

lib: $(OBJS)
	@ar rc $(NAME) $(addprefix objs/, $(OBJS))
	@ranlib $(NAME)

%.o: %.c
	mkdir -p objs
	gcc -g $(INCLUDES) -c $< -o objs/$@

build:
	@cat $(CL_FILES) > $(CL_FINAL)

run : all
	@./testcl
