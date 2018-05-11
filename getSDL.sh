#!/bin/sh

if ! [ -x sdl2-config ] ; then
	cd vendor/SDL/
	if ! [ -f bin/sdl2-config ] ; then
		./install.sh SDL2-2.0.8
		./install.sh SDL2_ttf-2.0.14 projects/SDL_ttf/
		./install.sh SDL2_image-2.0.3 projects/SDL_image/
		fi
	echo SDL local
	echo `./bin/sdl2-config --cflags` > ../../.sdl_includes
	echo `./bin/sdl2-config --libs` > ../../.sdl_links
else
	echo SDL global
	echo `sdl2-config --cflags` > ../../.sdl_includes
	echo `./bin/sdl2-config --libs` > ../../.sdl_links
fi