SRCS = opencl.c erasecl.c readcl.c err.c
TEST= tests/test_intersect.c
SRCS:= $(addprefix srcs/, $(SRCS))
OBJS = $(SRCS:.c=.o)
INCLUDES := . ../../libft ../objects ../maths/vec3f
INCLUDES := $(addprefix -I, $(INCLUDES))
CL_FILES=../maths/vec3f/vec3f.cl ../maths/maths.cl ../objects/sphere.cl
CL_FINAL=all.cl

vpath %.o objs

all : fclean build
	@echo -e "\e[31m compilation de $(TEST) \e[0m"
@gcc $(INCLUDES) -Llibft -lft -framework OpenCL opencl.a $(TEST) -o testcl

lib: $(OBJS)
	ar rc opencl.a $(OBJS)
	ranlib opencl.a

%.o: %.c
	gcc $(INCLUDES) -c $< -o $@

build:
	@cat $(CL_FILES) > $(CL_FINAL)

run : all
	@./testcl

fclean :
	@rm -rf testcl
