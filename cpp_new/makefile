FLAGS = -O0 -ggdb -pedantic -Wall -Wextra
INCLUDE = -I.

all: hsm.cpp test.cpp
	g++ test.cpp hsm.cpp -o test $(FLAGS)

clean:
	rm -f *.exe
	rm -f *.o