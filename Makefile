objects = delta.o file_t.o paragraph.o printer.o
COMPILER = clang

delta: $(objects)
	$(COMPILER) -o delta $(objects)
delta.o: delta.c
	$(COMPILER) -c delta.c
file_t.o: src/file_t.c includes/file_t.h
	$(COMPILER) -c src/file_t.c
paragraph.o: src/paragraph.c includes/paragraph.h
	$(COMPILER) -c src/paragraph.c
printer.o: src/printer.c includes/printer.h
	$(COMPILER) -c src/printer.c
clean:
	rm delta $(objects)
