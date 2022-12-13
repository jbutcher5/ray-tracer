SRC = main.cpp math_utils.cpp vector.cpp objects.cpp
OBJ = ${SRC:.cpp=.o}

%.o: %.c
	clang++ -c -g $< -o $@

ray-tracer: ${OBJ}
	clang++ $^ -lnetpbm -lm -o $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -p *.o
