FLAGS = -O0 -ggdb -Wall
INCLUDE = -I.

hsm: hsm_engine.c
	gcc $(FLAGS) $(INCLUDE) hsm_engine.c -c

test: test_hsm.c
	gcc $(FLAGS) $(INCLUDE) test_hsm.c -c

main: main.c
	gcc $(FLAGS) $(INCLUDE) main.c -c

all: hsm test main
	gcc $(FLAGS) main.o hsm_engine.o test_hsm.o -o program

clean:
	rm -f program.exe
	rm -f *.o