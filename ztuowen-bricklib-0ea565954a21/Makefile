CC=icpc
EXAMPLE=cns
OPT=-Iinc -D_EX_$(EXAMPLE) -O2 -xMIC-AVX512 -qopenmp -std=c++11 -fimf-precision=low -fast-transcendentals -no-prec-sqrt -no-prec-div -fp-model fast=2 -fno-protect-parens -rcd -ftz -fma -fimf-domain-exclusion=none -qopt-assume-safe-padding $(EXTRA)
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix src/,$(notdir $(SRC:.cpp=.o)))

all:brick-test

src/%.o:src/%.cpp
	$(CC) $(OPT) -c -o $@ $^

brick-test:main.cpp $(OBJ)
	$(CC) $(OPT) -o $@ $^

san:san-check.cpp $(OBJ)
	$(CC) $(OPT) -o $@ $^

test-all:brick-test
	./brick-test 72
	./brick-test 136

clean:
	-rm ./brick-test

.PHONY:all test-all clean
