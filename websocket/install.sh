#!/bin/sh

#git submodule init && git submodule update
echo "\033[32mINSTALLING DEPS VIA BREW"
mkdir -p obj
brew install libtool gnu-sed openssl libevent
echo "\033[32mREPLACE STUFF WITH SED"
gsed -r -i "s/^libtoolize/glibtoolize/" libwebsock/autogen.sh
gsed -i "s/inline//g" libwebsock/src/utf*
echo "\033[33m making lib \033[0m"
