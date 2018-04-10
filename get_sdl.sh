#!/bin/bash

if [ -d "SDL2-2.0.8" ]
then
	echo "SDL OK"
else
	sh installSDL.sh
fi
