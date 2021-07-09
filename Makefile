OBJECTS = src/*.c

all:
	gcc -ggdb3 main.c ${OBJECTS} -o programaTrab -Wall

run:
	./programaTrab

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./programaTrab

gdb:
	gdb programaTrab


# Windows-specific
c:
	gcc -ggdb3 main.c ${OBJECTS} -o programaTrab.exe -Wall

d:
	gcc -g main.c ${OBJECTS} -o programaTrab.exe -Wall
	gdb programaTrab.exe

r:
	gcc main.c ${OBJECTS} -o programaTrab.exe -Wall
	programaTrab.exe

clean:
	rm ./*bin ./*csv programaTrab.exe