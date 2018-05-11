include includes.dep

NAME=rtv1
SANITIZE = ""
COMPILE=gcc -g $(SANITIZE) #-O3

all: libft SDL2 $(NAME)
	@printf "\033[1A\r\033[K""\r\033[K""\033[32m[RT Compilé]\033[0m\n"

$(NAME): $(OBJS) $(HEADERS)
	$(COMPILE) $(INCLUDE) $(PATH_OBJ) `cat .sdl_links` $(LINK) -o $(NAME)

sanitize:
	$(eval SANITIZE = -fsanitize=address)
	make all

# Vérifie si SDL2 exist, sinon l'installe.
SDL2:
	@./vendor/SDL/getsdl.sh

# Compilation des fichiers .c en les cherchant selon le VPATH.
%.o : %.c $(HEADERS)
	@mkdir -p $(OPATH)
	@$(COMPILE) $(INCLUDE) `cat .sdl_includes` -c $< -o $(OPATH)$@
	@printf "\033[1A\r\033[K""\r\033[K""\033[32m[RT] \033[0m""Compilation de "$@"\n"

# Liste des rêgles de base d'un Makefile :
clean :
	@$(MAKE) -C libft clean
	@rm -rf $(OPATH)
	@echo "Librairie et ressources supprimé."

fclean : clean
	@$(MAKE) -C libft fclean
	@rm -rf $(NAME)
	@echo "RT Supprimé."

re :  fclean all
#END OF LIST

# Liste des configuration préparé :
sujet: all
	@./$(NAME) configs/sujet/mul

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
	lldb ~/rtv1/rtv1 configs/config4

valgrind: all
	valgrind --leak-check=full ./$(NAME)

delib:
	cd vendor/SDL && rm -rf ./SDL2-2.0.8/ ./SDL2-2.0.8.tar.gz ./SDL2_image-2.0.3/ ./SDL2_image-2.0.3.tar.gz ./SDL2_ttf-2.0.14/ ./SDL2_ttf-2.0.14.tar.gz lib include bin share

.PHONY : libft SDL2
