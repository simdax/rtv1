echo getting SDL
curl -OL https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
echo untaring
tar xf SDL2-2.0.8.tar.gz
echo installing.
cd SDL2-2.0.8/ && ./configure && make

