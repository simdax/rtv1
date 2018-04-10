# Inclut les dépendance des fichiers nécessaire pour la compilation.
include src/brackets/make.dep
include src/maths/make.dep
include src/maths/vec3f/make.dep
include src/objects/make.dep

# Liste des chemins pour le Makefile :
BRAC=src/brackets/
MATH=src/maths/
VEC3=src/maths/vec3f/
OBJE=src/objects/
ALLPATH=$(BRAC) $(FORM) $(MATH) $(VEC3) src/ src/raytracing/

# Liste de tous les .c répertorié par le Makefile :
SRCS=main.c sdl.c thread.c
SRC=main.c sdl.c thread.c
SRCS_RT=fx.c diffuse.c trace.c
SRCS+=$(SRCS_RT) $(BRACKETS_SRCS) $(OBJECTS_SRCS) $(MATHS_SRCS) $(VEC3F_SRCS)

# Liste des chemins et de tous leur .c respectif.
# Cela divisera les rêgles du Makefile pour permettre une compilation par étapes.
PBRAC=$(addprefix src/brackets/, $(BRACKETS_SRCS))
PFORM=$(addprefix src/objects/, $(OBJECTS_SRCS))
PMATH=$(addprefix src/maths/, $(MATHS_SRCS))
PVEC3=$(addprefix src/maths/vec3f/, $(VEC3F_SRCS))
PATH_SRCS:=$(addprefix src/, $(SRC))
PATH_SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
ALLC=$(PBRAC) $(PFORM) $(PMATH) $(PVEC3) $(PATH_SRCS) $(PATH_SRCS_RT)

# Liste les différents INCLUDES nécessaire au Makefile :
LINK=`sdl2-config --libs` -lm -Llibft -lft -lpthread #LSDL2-2.0.8/build/.libs -lSDL2
HEADERS=rtv1.h
INCLUDE=. src/brackets/ src/maths/ src/maths/vec3f src/objects/ libft ./
INCLUDE:=$(addprefix -I, $(INCLUDE)) $(shell sdl2-config --cflags)
COMPILE=gcc -g #-O3
NAME=rtv1

# Insert les .o dans un seul dossier obj/
OBJS=$(SRCS:%.c=%.o)
OPATH= obj/
PATH_OBJ=$(addprefix $(OPATH), $(OBJS))

all: libft $(PATH_OBJ) $(HEADERS)
	@printf "\r\033[K""\r\033[K""\033[32m[RT Compilé]\033[0m\n"
	@$(COMPILE) $(INCLUDE) $(PATH_OBJ) $(LINK) -o $(NAME)

# Liste les différentes règles pour chaque .o nécessaireà la compilation final.
# La liste est dans l'ordre exact passé par la liste des fichiers .c (ligne 14).
$(OPATH)%.o : src/%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[SOURCE] \033[0m""Compilation de "$@

$(OPATH)%.o : src/raytracing/%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[RAYTRACER] \033[0m""Compilation de "$@

$(OPATH)%.o : $(BRAC)%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[BRACKET] \033[0m""Compilation de "$@

$(OPATH)%.o : $(OBJE)%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[OBJET] \033[0m""Compilation de "$@

$(OPATH)%.o : $(VEC3)%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[VECTEUR] \033[0m""Compilation de "$@

$(OPATH)%.o : $(MATH)%.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) -c $< -o $@
	@printf "\r\033[K""\r\033[K""\033[32m[MATH] \033[0m""Compilation de "$@
#END OF LIST


# Liste des rêgles de base d'un Makefile :
clean :
	@$(MAKE) -C libft clean
	@rm -rf $(OPATH)
	@echo "Librairie et ressources supprimé."

fclean :
	@$(MAKE) -C libft fclean
	@rm -rf $(OPATH)
	@rm -rf $(NAME)
	@echo "RT Supprimé."

re : fclean all
#END OF LIST

# Liste des configuration préparé :
config1: all
	@./$(NAME) configs/config

config2: all
	@./$(NAME) configs/config2

config3: all
	@./$(NAME) configs/config3

config4: all
	@./$(NAME) configs/config4

config5: all
	@./$(NAME) configs/config5
#END OF LIST


# Petite liste de Make pour la norm :
norm:
	@clear
	@norminette $(ALLC)

normall: clean norm
	@make -C libft norminette

normlib: clean
	@make -C libft norminette
#END OF LIST


compile: libft $(SRCS) $(HEADERS)
	$(COMPILE) $(INCLUDE) $(PATH_OBJ) -o $(NAME)

libft:
	@make -j -C libft

debug: all
	gdb --fullname --args ~/rtv1/rtv1 configs/config2

valgrind: all
	valgrind --leak-check=full ./$(NAME)

.PHONY : libft
