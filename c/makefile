FLAGS = -O0 -ggdb -pedantic -Wall -Wextra
INCLUDE = -I.

all: watch.c hsm.c hsmtst.c
	gcc watch.c hsm.c -o watch $(FLAGS)
	gcc hsmtst.c hsm.c -o hsmtst $(FLAGS)

clean:
	rm -f *.exe
	rm -f *.o