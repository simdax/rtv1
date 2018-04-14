#!/bin/bash

get_sdl()
{
	sdl2-config &> /dev/null
	if [ $? -eq 1 ]
	then
		printf "\r\033[K""\r\033[K""\033[32m[SDL Installé]\033[0m\n"
	else
		sh installSDL.sh
	fi
}
