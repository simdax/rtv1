echo getting SDL_image
curl -OL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz
echo untaring
tar xf SDL2_image-2.0.3.tar.gz
echo installing.
cd SDL2_image-2.0.3/ && ./configure && make
