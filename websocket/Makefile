NAME=websocket
LIB_WEBSOCK_PATH=libwebsock/src/.libs
LIB_WEBSOCK=$(LIB_WEBSOCK_PATH)/libwebsock.so

all: $(NAME)

$(NAME): $(LIB_WEBSOCK)
	gcc -g -O2 -o $(NAME) test.c -L$(LIB_WEBSOCK_PATH) -lwebsock

$(LIB_WEBSOCK):
	sed -i "s/inline//g" libwebsock/src/utf*
	cd libwebsock && ./autogen.sh && CFLAGS="-lpthread -levent" ./configure && make

run: all
	./$(NAME) 5678 &
	firefox hello.html
