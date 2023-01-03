SRC = main.cpp math_utils.cpp vector.cpp objects.cpp image.cpp scene.cpp materials.cpp
OBJ = ${SRC:.cpp=.o}

%.o: %.cpp
	clang++ -c -fopenmp -g $< -o $@

ray-tracer: ${OBJ}
	clang++ $^ -g -lomp -lnetpbm -lm -o $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -p *.o
