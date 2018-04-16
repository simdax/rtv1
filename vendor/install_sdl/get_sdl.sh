#!/bin/bash
if [ -f ~/.brew/include/SDL2/SDL.h ] && [ -f ~/.brew/lib/libSDL2.a ];
	then printf " $(bash sdl2-config --libs)" > include.dep; echo '\033[36m[SDL Installé]\033[0m';
	else if [ -f ./SDL2-2.0.8/include/SDL.h ] && [ -f ./SDL2-2.0.8/build/.libs/libSDL2.a ];
		then printf ' ./SDL2-2.0.8/build/.libs/libSDL2.a' > include.dep; echo '\033[36m[SDL externe Installé]\033[0m';
		else sh ./vendor/install_sdl/installSDL.sh; printf ' ./SDL2-2.0.8/build/.libs/libSDL2.a' > include.dep; echo '\033[1;36m[SDL externe a été installé]\033[0m' ;
		fi
	fi

if [ -f ~/.brew/include/SDL2/SDL_image.h ];
	then printf '-lSDL_image' >> include.dep; echo  '\033[36m[SDL_image Installé]\033[0m';
	else if [ -f ./SDL2_image-2.0.3/libSDL2_image.la ] && [ -f ./SDL2_image-2.0.3/SDL_image.h ];
		then printf ' -ISDL2_image-2.0.3/ ./SDL2_image-2.0.3/.libs/libSDL2_image.a' >> include.dep; echo '\033[36m[SDL_image externe Installé]\033[0m';
		else sh ./vendor/install_sdl/installSDL_img.sh; printf ' -ISDL2_image-2.0.3/ ./SDL2_image-2.0.3/.libs/libSDL2_image.a' >> include.dep; echo '\033[1;36m[SDL_image a été installé]\033[0m' ;
		fi
	fi

if [ -f ~/.brew/include/SDL2/SDL_ttf.h ];
	then printf ' -lSDL_ttf' >> include.dep; echo '\033[36m[SDL_ttf Installé]\n\033[0m';
	else if [ -f ./SDL2_ttf-2.0.14/SDL_ttf.h ] && [ -f ./SDL2_ttf-2.0.14/libSDL2_ttf.la ];
		then printf ' -I./SDL2_ttf-2.0.14/ ./SDL2_ttf-2.0.14/.libs/libSDL2_ttf.a' >> include.dep; echo '\033[36m[SDL_ttf externe Installé]\n\033[0m';
		else sh ./vendor/install_sdl/installSDL_ttf.sh; printf ' -I./SDL2_ttf-2.0.14/ ./SDL2_ttf-2.0.14/.libs/libSDL2_ttf.a' >> include.dep; echo '\033[1;36m[SDL_ttf a été installé]\n\033[0m' ;
		fi
	fi
