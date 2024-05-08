FLAGS = -O0 -ggdb -pedantic -Wall -Wextra
INCLUDE = -I.

all: watch.cpp hsm.cpp hsmtst.cpp
	g++ watch.cpp hsm.cpp -o watch $(FLAGS)
	g++ hsmtst.cpp hsm.cpp -o hsmtst $(FLAGS)

clean:
	rm -f *.exe
	rm -f *.o