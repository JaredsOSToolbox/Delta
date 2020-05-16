objects: delta.o para.o utils.o
COMPILER = clang
OUTPUT = delta

all: delta run

delta: $(objects)
	$(COMPILER) $(objects) -o $(OUTPUT)
delta.o: diff_02.c
	$(COMPILER) -c -g diff_02.c -o delta.o
para.o: para.c para.h
	clang -c -g para.c
utils.o: util.c util.h
	clang -c -g util.c
clean_objects: $(objects)
	rm $(objects)
clean:
	rm $(OUTPUT)
run:
	./$(OUTPUT)
