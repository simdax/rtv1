#!/bin/sh

git submodule init && git submodule update
brew install libtool gnu-sed openssl libevent
gsed -r -i "s/^libtoolize/glibtoolize/" libwebsock/autogen.sh
gsed -i "s/inline//g" libwebsock/src/utf*
