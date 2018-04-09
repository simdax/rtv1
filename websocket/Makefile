LIB_WEBSOCK_PATH=libwebsock/src/.libs
LIB_WEBSOCK=$(LIB_WEBSOCK_PATH)/libwebsock.so

all: $(LIB_WEBSOCK)
	gcc -g -O2 -o test test.c -L$(LIB_WEBSOCK_PATH) -lwebsock

$(LIB_WEBSOCK):
	sed -i "s/inline//g" libwebsock/src/utf*
	cd libwebsock && ./autogen.sh && CFLAGS="-lpthread -levent" ./configure && make

run: all
	./test 5678 &
	firefox hello.html
