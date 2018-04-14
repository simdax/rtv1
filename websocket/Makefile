NAME=websocket
LIB_WEBSOCK_PATH=libwebsock/src/.libs
LIB_WEBSOCK=$(LIB_WEBSOCK_PATH)/libwebsock.so

BREW=/Users/scornaz/.brew/Cellar
LIBEVENT=libevent/2.1.8
OPENSSL=openssl/1.0.2o_1
CFLAGS=-I $(BREW)/$(LIBEVENT)/include/ -I $(BREW)/$(OPENSSL)/include/
LFLAGS=-L$(BREW)/$(LIBEVENT)/lib -levent -levent_openssl -levent_core -levent_pthreads -L$(BREW)/$(OPENSSL)/lib -lssl -lcrypto
CONFIGURE=CFLAGS='$(CFLAGS) $(LFLAGS)' ./configure

all: $(NAME)

$(NAME): test.c
	gcc -g -O2 -o $(NAME) $(CFLAGS) test.c -L$(LIB_WEBSOCK_PATH) $(LFLAGS) -lpthread

$(LIB_WEBSOCK):
	gsed -i "s/inline//g" libwebsock/src/utf*
	cd libwebsock && ./autogen.sh && $(CONFIGURE) && make

run: all
	firefox hello.html &
	./$(NAME)
