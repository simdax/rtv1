# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alerandy <alerandy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/17 16:41:43 by alerandy          #+#    #+#              #
#    Updated: 2018/04/26 17:30:48 by alerandy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Inclut les dépendance des fichiers nécessaire pour la compilation.
include src/brackets/make.dep
include src/maths/make.dep
include src/maths/vec3f/make.dep
include src/objects/make.dep
include src/SDL/sdl_mouse/make.dep
include src/minils/make.dep
include ./src/launcher/make.dep

# Liste des chemins pour le Makefile :
VPATH=.:obj:$(shell find src -type d | tr '\n' ':')

# libft modules
LIBFT_MODULES=$(addprefix -I libft/, string mem array printf/includes gnl .)

# Liste de tous les .c répertorié par le Makefile :
SRCS+=main.c sdl.c thread.c
SRC=main.c render/sdl.c render/thread.c
SRCS_RT=fx.c diffuse.c trace.c
SRCS+=$(SRCS_RT) $(SRCS_RENDER) $(BRACKETS_SRCS) $(BRACKETS_SRCS_T) $(OBJECTS_SRCS) $(MATHS_SRCS) $(VEC3F_SRCS)\
	  $(SDL_MOUSE_SRCS) $(SRC_MINI_LS)

# Liste des chemins et de tous leur .c respectif.
# Cela divisera les rêgles du Makefile pour permettre une compilation par étapes.
PBRAC=$(addprefix src/brackets/srcs/, $(BRACKETS_SRCS))
PBRAT=$(addprefix src/brackets/srcs/types/, $(BRACKETS_SRCS_T))
PFORM=$(addprefix src/objects/, $(OBJECTS_SRCS))
PMATH=$(addprefix src/maths/, $(MATHS_SRCS))
PVEC3=$(addprefix src/maths/vec3f/, $(VEC3F_SRCS))
PATH_SRCS:=$(addprefix src/, $(SRC))
PATH_SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
# sdl_mouse Submodule
PMOUS=$(addprefix src/SDL/sdl_mouse/, $(SDL_MOUSE_SRCS))
PMINI=$(addprefix src/minils/, $(SRC_MINI_LS))
ALLC+=$(PBRAC) $(PBRAT) $(PFORM) $(PMATH) $(PVEC3) $(PATH_SRCS) $(PATH_SRCS_RT) $(PMOUS) $(PMINI)

# Liste les différents INCLUDES nécessaire au Makefile :
LINK= -lm -Llibft -lft -lpthread -framework Appkit
HEADERS=rtv1.h
INCLUDE+= . src/brackets/ src/maths/ src/maths/vec3f src/objects/\
		  SDL2_ttf-2.0.14/ SDL2_image-2.0.3/
INCLUDE:=$(addprefix -I, $(INCLUDE)) $(shell sdl2-config --cflags)
INCLUDE+= $(LIBFT_MODULES)
COMPILE=gcc -g #-O3
NAME=rtv1


# Insert les .o dans un seul dossier obj/
OBJS=$(SRCS:%.c=%.o)
OPATH= obj/
PATH_OBJ=$(addprefix $(OPATH), $(OBJS))


all: SDL2 libft $(NAME)
	@printf "\033[1A\r\033[K""\r\033[K""\033[32m[RT Compilé]\033[0m\n"

$(NAME): $(OBJS) $(HEADERS)
	@$(COMPILE) $(INCLUDE) $(PATH_OBJ) $(LINK) $(LINK2) -o $(NAME)

# Vérifie si SDL2 exist, sinon l'installe.
SDL2:
	@sh ./vendor/install_sdl/get_sdl.sh
	@rm -rf ./SDL2_image-2.0.3/.libs/libSDL2_image.dylib
	@rm -rf ./SDL2_ttf-2.0.14/.libs/libSDL2_ttf-2.0.0.dylib
	@$(eval LINK2=`cat ./include.dep`)

# Compilation des fichiers .c en les cherchant selon le VPATH.
%.o : %.c
	@mkdir -p $(OPATH)
	@printf "\033[1A\r\033[K""\r\033[K""\033[32m[RT] \033[0m""Compilation de "$@"\n"
	@$(COMPILE) $(INCLUDE) -c $< -o $(OPATH)$@


# Liste des rêgles de base d'un Makefile :
clean :
	@$(MAKE) -C libft clean
	@rm -rf $(OPATH)
	@echo "Librairie et ressources supprimé."

fclean :
	@$(MAKE) -C libft fclean
	@rm -rf $(OPATH)
	@rm -rf $(NAME)
	@rm -rf include.dep
	@echo "RT Supprimé."

re : fclean all
#END OF LIST

# Petite liste de Make pour la norm :
norm:
	@clear
	@echo "\033[33mScan des fichiers .h :\033[0m"
	@norminette $(shell find src -regex ".\{1,200\}\.h" | xargs)
	@echo "\n\033[33mScan des fichiers .c :\033[0m"
	@norminette $(ALLC)

normall: clean norm
	@make -C libft norminette

normlib: clean
	@make -C libft norminette
#END OF LIST

libft:
	@git submodule init
	@git submodule update
	@make -j -C libft

debug: all
	gdb --fullname --args ~/rtv1/rtv1 configs/config2

valgrind: all
	valgrind --leak-check=full ./$(NAME)

delib:
	@rm -rf ./SDL2-2.0.8/ ./SDL2-2.0.8.tar.gz ./SDL2_image-2.0.3/ ./SDL2_image-2.0.3.tar.gz ./SDL2_ttf-2.0.14/ ./SDL2_ttf-2.0.14.tar.gz
	@echo "Librairies supprimées."

delall : fclean delib

.PHONY : libft SDL2
