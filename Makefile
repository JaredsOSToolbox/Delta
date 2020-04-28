all:
	clang src/*.c delta.c -o delta
	./delta
