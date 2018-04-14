#!/bin/bash
<<<<<<< HEAD

=======
get_sdl()
{
>>>>>>> 450b01d13f2c70c63f4580cb066da10be4cda171
sdl2-config &> /dev/null
if [ $? -eq 1 ]
then
	printf "\r\033[K""\r\033[K""\033[32m[SDL Installé]\033[0m\n"
else
	sh installSDL.sh
fi
<<<<<<< HEAD
=======
}

get_sdl
>>>>>>> 450b01d13f2c70c63f4580cb066da10be4cda171
