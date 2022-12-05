SRC = main.c
OBJ = ${SRC:.c=.o}

%.o: %.c
	clang -c -g $< -o $@

ray-tracer: ${OBJ}
	clang $^ -o $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -p *.o
