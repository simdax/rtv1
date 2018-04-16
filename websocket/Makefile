VPATH=srcs/:./

NAME=websocket
SRCS=websocket_test.c api.c websocket_interface.c
OBJS=$(SRCS:%.c=%.o)

LIB_WEBSOCK_PATH=libwebsock/src/.libs
LIB_WEBSOCK=$(LIB_WEBSOCK_PATH)/libwebsock.so

BREW=/Users/scornaz/.brew/Cellar
LIBEVENT=libevent/2.1.8
OPENSSL=openssl/1.0.2o_1
CFLAGS=-I $(BREW)/$(LIBEVENT)/include/ -I $(BREW)/$(OPENSSL)/include/
LFLAGS=-L$(BREW)/$(LIBEVENT)/lib -levent -levent_openssl -levent_core -levent_pthreads -L$(BREW)/$(OPENSSL)/lib -lssl -lcrypto
CONFIGURE=CFLAGS='$(CFLAGS) $(LFLAGS)' ./configure

all: $(LIB_WEBSOCK) $(NAME)

$(NAME): $(OBJS)
	gcc -g -O2 -o $(NAME) $(addprefix obj/, $(OBJS)) -L$(LIB_WEBSOCK_PATH) -lwebsock -lpthread

%.o:%.c | obj
	gcc -g -o obj/$@ $(CFLAGS) -Iincludes -Ilibwebsock/src -c $<

$(LIB_WEBSOCK):
	./install.sh
	cd libwebsock && ./autogen.sh && $(CONFIGURE) && make

run: all
	open -a "Google Chrome" web_interface/index.html &
	DYLD_LIBRARY_PATH=$(LIB_WEBSOCK_PATH) ./$(NAME)
