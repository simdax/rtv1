# Inclut les dépendance des fichiers nécessaire pour la compilation.
include src/brackets/make.dep
include src/maths/make.dep
include src/maths/vec3f/make.dep
include src/objects/make.dep

# Liste des chemins pour le Makefile :
VPATH=.:obj:$(shell find src -type d | tr '\n' ':')

# Liste de tous les .c répertorié par le Makefile :
SRCS=main.c sdl.c thread.c
SRC=main.c sdl.c thread.c
SRCS_RT=fx.c diffuse.c trace.c
SRC_MOUS=button.c main.c media_loader.c texture.c texture2.c
SRCS+=$(SRCS_RT) $(BRACKETS_SRCS) $(OBJECTS_SRCS) $(MATHS_SRCS) $(VEC3F_SRCS) \
	  #$(SRC_MOUS)

# Liste des chemins et de tous leur .c respectif.
# Cela divisera les rêgles du Makefile pour permettre une compilation par étapes.
PBRAC=$(addprefix src/brackets/, $(BRACKETS_SRCS))
PFORM=$(addprefix src/objects/, $(OBJECTS_SRCS))
PMATH=$(addprefix src/maths/, $(MATHS_SRCS))
PVEC3=$(addprefix src/maths/vec3f/, $(VEC3F_SRCS))
PATH_SRCS:=$(addprefix src/, $(SRC))
PATH_SRCS_RT:=$(addprefix src/raytracing/, $(SRCS_RT))
# sdl_mouse Submodule
PMOUSE=$(addprefix $(MOUS), $(SRCS_RT))
ALLC=$(PBRAC) $(PFORM) $(PMATH) $(PVEC3) $(PATH_SRCS) $(PATH_SRCS_RT) $(PMOUSE)

# Liste les différents INCLUDES nécessaire au Makefile :
LINK= -lm -Llibft -lft -lpthread
HEADERS=rtv1.h
INCLUDE= . src/brackets/ src/maths/ src/maths/vec3f src/objects/ libft \
		  libft/string libft/mem libft/array libft/printf/includes \
		  $(addprefix $(VENDOR_PATH), SDL2_ttf-2.0.14/ SDL2_image-2.0.3)
INCLUDE:=$(addprefix -I, $(INCLUDE)) $(shell sdl2-config --cflags)
COMPILE=gcc -g #-O3
NAME=rtv1

# Insert les .o dans un seul dossier obj/
OBJS=$(SRCS:%.c=%.o)
OPATH= obj/
PATH_OBJ=$(addprefix $(OPATH), $(OBJS))


all: SDL2 libft $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(COMPILE) $(INCLUDE) $(PATH_OBJ) $(LINK) $(LINK2) $(LINK3) $(LINK4) -o $(NAME)
	@printf "\r\033[K""\r\033[K""\033[32m[RT Compilé]\033[0m\n"

TEST:
	@if [ -f ~/.brew/include/SDL2/SDL_image.h ] ;\
		then echo $(INCLUDE) $(eval INCLUDE= -I./SDL_ttf-2.0.14/) $(INCLUDE);\
		else \
		if [ -f ~/.brew/include/SDL2/SDL_image.h ] ;\
		then echo $(INCLUDE) $(eval INCLUDE= -I./SDL_image-2.0.3/) $(INCLUDE); else\
		echo $(INCLUDE) $(eval INCLUDE= -I./SDL_2.0.8/) $(INCLUDE); fi\
		fi

# Vérifie si SDL2 exist, sinon l'installe.
SDL2:
	 @if [ -f ~/.brew/include/SDL2/SDL.h ] && [ -f ~/.brew/lib/libSDL2.a ];\
		 then echo $(eval LINK2=$(shell sdl2-config --libs))\
		 $(eval INCLUDE2=$(shell sdl2-config --cflags)) [SDL installé];\
		 else\
		 if [ -f ./SDL2-2.0.8/include/SDL.h ] || [ -f ./SDL2-2.0.8/build/.libs/libSDL2.a ];\
		 then echo $(eval LINK2= -L./SDL2-2.0.8/build/.libs/ -lSDL2)\
		 $(eval INCLUDE2= -I./SDL2-2.0.8/include/) [SDL installé];\
		 else echo sh ./vendor/install_sdl/installSDL.sh $(eval LINK2= -L./SDL2-2.0.8/build/.libs/ -lSDL2)\
		 $(eval INCLUDE2= -I./SDL2-2.0.8/include/) [SDL a été installé]; fi\
		 fi
	 @if [ -f ~/.brew/include/SDL2/SDL_image.h ] ; then echo $(eval LINK3= -lSDL2_image)\
		 [SDL_image Installé]; else\
		 if [ -f ./SDL2_image-2.0.3/libSDL2_image.la ] && [ -f ./SDL2_image-2.0.3/SDL_image.h ]; then\
		 echo $(eval INCLUDE3= -ISDL2_image-2.0.3/) $(eval LINK3= -L./SDL2_image-2.0.3/.libs/ -lSDL2_image)\
		 '[SDL_image externe installé]'; else echo sh ./vendor/install_sdl/installSDL_img.sh\
		 $(eval INCLUDE3= -ISDL2_image-2.0.3/) $(eval LINK3= -LSDL2_image-2.0.3/.libs -lSDL2_image)\
		 "\n\n[SDL a été installé]\n"; fi\
		 fi
	 @if [ -f ~/.brew/include/SDL2/SDL_ttf.h ];\
		 then echo $(eval LINK4= -lSDL_ttf) [SDL_ttf Installé]; else\
		 if [ -f ./SDL2_ttf-2.0.14/SDL_ttf.h ] && [ -f ./SDL2_ttf-2.0.14/libSDL2_ttf.la ]; then\
		 echo $(eval INCLUDE4= -I./SDL2_ttf-2.0.14/) $(eval LINK4= -LSDL2_ttf-2.0.14/.libs -lSDL2_ttf)\
		 '[SDL_ttf externe installé]' ; else sh ./vendor/install_sdl/installSDL_ttf.sh\
		 echo $(eval INCLUDE4= -I./SDL2_ttf-2.0.14/) $(eval LINK4= -LSDL2_ttf-2.0.14/.libs -lSDL2_ttf)\
		 "\n\n[SDL_ttf a été installé]\n"; fi\
		 fi



# Compilation des fichiers .c en les cherchant selon le VPATH.
%.o : %.c
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) $(INCLUDE2) $(INCLUDE3) $(INCLUDE4) -c $< -o $(OPATH)$@
	@printf "\033[1A\r\033[K""\r\033[K""\033[32m[RT] \033[0m""Compilation de "$@"\n"


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
	@norminette $(shell find src -regex ".\{1,200\}\.h" | xargs) $(ALLC)

normall: clean norm
	@make -C libft norminette

normlib: clean
	@make -C libft norminette
#END OF LIST

libft:
	@make -j -C libft

debug: all
	gdb --fullname --args ~/rtv1/rtv1 configs/config2

valgrind: all
	valgrind --leak-check=full ./$(NAME)

delib:
	rm -rf ./SDL2-2.0.8/ ./SDL2-2.0.8.tar.gz ./SDL2_image-2.0.3/ ./SDL2_image-2.0.3.tar.gz ./SDL2_ttf-2.0.14/ ./SDL2_ttf-2.0.14.tar.gz

.PHONY : libft SDL2
