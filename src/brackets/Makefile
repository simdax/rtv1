LIBFT_PATH=../../libft

all:
	gcc -g brackets.c -L$(LIBFT_PATH) -I$(LIBFT_PATH) -lft
	./a.out "salut mec" "salut (mec)"
	 ./a.out "()" "(fdsafds)" "((())"
	 ./a.out "(bon)(jour)" ")" "(des tru (cs de) ouf)"
	 ./a.out "fdasfsd" "(((a b c )(\nfdfds)(d e))(f g h)())()"
	 ./a.out "sphere (0 1 2) (2 4 5) (5 4 6) bob		 (fds) "

type:
	gcc type.h && ./a.out
