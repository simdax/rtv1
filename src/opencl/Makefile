SRCS = opencl.c erasecl.c readcl.c err.c
TEST= tests/test_intersect.c
SRCS:= $(addprefix srcs/, $(SRCS))
INCLUDES := . ../../libft ../objects ../maths/vec3f
INCLUDES := $(addprefix -I, $(INCLUDES))

CL_FILES=../maths/vec3f/vec3f.cl ../maths/maths.cl ../objects/sphere.cl
CL_FINAL=all.cl

all : fclean build
	gcc $(INCLUDES) -Llibft -lft -framework OpenCL $(SRCS) $(TEST) -o testcl

build:
	cat $(CL_FILES) > $(CL_FINAL)

run : all
	@./testcl

fclean :
	rm -rf testcl
