all:
	clang src/*.c delta.c -o delta
	./delta

# delta.h  file_struct.h	paragraph.h  printer.h
# file_struct.c  paragraph.c  printer.c
#
