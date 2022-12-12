SRC = main.c objects.c math_utils.c
OBJ = ${SRC:.c=.o}

%.o: %.c
	clang -c -g $< -o $@

ray-tracer: ${OBJ}
	clang $^ -lnetpbm -lm -o $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -p *.o
