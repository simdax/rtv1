echo getting SDL_image
curl -OL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
echo untaring
tar xf SDL2_ttf-2.0.14.tar.gz
echo installing.
cd SDL2_ttf-2.0.14/ && ./configure && make
