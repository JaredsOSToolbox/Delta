objects = assert_tests.o delta.o file_t.o paragraph.o printer.o
COMPILER = clang
OUTPUT = delta

all: delta run

delta: $(objects)
	$(COMPILER) -o $(OUTPUT) $(objects)
delta.o: delta.c
	$(COMPILER) -c delta.c
assert_tests.o: src/assert_tests.c includes/assert_tests.h
	$(COMPILER) -c -g src/assert_tests.c
file_t.o: src/file_t.c includes/file_t.h
	$(COMPILER) -c -g src/file_t.c
paragraph.o: src/paragraph.c includes/paragraph.h
	$(COMPILER) -c -g src/paragraph.c
printer.o: src/printer.c includes/printer.h
	$(COMPILER) -c -g src/printer.c
run:
	./$(OUTPUT)
clean: object_clean
	rm $(OUTPUT)
object_clean:
	rm $(objects)
