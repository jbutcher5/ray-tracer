SRC = main.cpp math_utils.cpp vector.cpp objects.cpp image.cpp scene.cpp
OBJ = ${SRC:.cpp=.o}

%.o: %.c
	clang++ -c -g $< -o $@

ray-tracer: ${OBJ}
	clang++ $^ -g -lnetpbm -lm -o $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -p *.o
