NAME = libft.a

FLAGS := -Wall -Werror -Wextra
CC := gcc -g
FILES := ft_nbrsize.c ft_rotate.c ft_swapchar.c ft_tolower.c ft_toupper.c
DEPS = string/make.dep list/make.dep array/make.dep gnl/make.dep unicode/make.dep mem/make.dep print/make.dep numbers/make.dep maths/make.dep

include string/make.dep
include list/make.dep
include array/make.dep
include gnl/make.dep
include unicode/make.dep
include mem/make.dep
include print/make.dep
include numbers/make.dep
include maths/make.dep	

OBJS := $(FILES:%.c=%.o)
INCLUDES := $(addprefix -I, . $(INCLUDES))

all: $(NAME) $(DEPS)
	@printf "\r\033[K""\r\033[K""\033[32m[LIBFT OK]\033[0m\n"

%.o: %.c
	@$(CC) -c $(INCLUDES) $(FLAGS) $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[LIBFT] \033[0m""Compilation de "$@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

norminette:
	@norminette
