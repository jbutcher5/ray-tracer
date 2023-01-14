CC      = clang++
INCLUDE = src
OBJ     = build
SRC     = src
SRCS    = $(SRC)/main.cpp
SRCS    += $(wildcard $(SRC)/*.cpp)
SRCS    += $(wildcard $(SRC)/*/*.cpp)
SRCS    += $(wildcard $(SRC)/*/*/*.cpp)
OBJS    = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
EXE     = rt
CFLAGS  = -I$(INCLUDE) -std=c++17 -fopenmp
LDLIBS  = -lomp -lnetpbm -lm

$(OBJ)/%.o: $(SRC)/%.cpp
	clang++ -c $(CFLAGS) -g $< -o $@

$(EXE): ${OBJS}
	clang++ $^ -g $(LDLIBS) -o $@

$(OBJ):
	mkdir -p $@

format: ${SRC}
	clang-format $^ -i

clean:
	rm -rf $(OBJ)
