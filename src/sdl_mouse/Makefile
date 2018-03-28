all: fclean
	gcc sdl_mouse.c texture.c texture2.c button.c `sdl2-config --cflags --libs` -lSDL2_image

fclean:
	rm -rf a.out
