all: fclean
	gcc -g sdl_mouse.c texture.c texture2.c button.c `sdl2-config --cflags --libs` -lSDL2_image

run: all
	./a.out

fclean:
	rm -rf a.out
