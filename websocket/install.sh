#!/bin/sh

brew install libtool gnu-sed openssl libevent
gsed -i "s/libtoolize/glibtoolize/" libwesock/autogen.sh
