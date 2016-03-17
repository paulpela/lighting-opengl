MAKEFLAGS=-j2
CC=clang++
OPTIMALIZATION=-O2
CFLAGS=-c -std=c++11 -gsplit-dwarf
LDFLAGS=-lglut -lGL -lGLU -lGLEW
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(shell basename ${PWD})

TEST_MAIN=main_test.cpp
TEST_CASES=$(wildcard c_*_test.cpp)
TEST_SOURCES=$(TEST_MAIN) $(TEST_CASES) $(CLASSES)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)
TEST_EXECUTABLE=catchtests

all: $(SOURCES) $(EXECUTABLE)

tests: $(TEST_SOURCES) $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $@ $(LDFLAGS) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run: all
	./$(EXECUTABLE)

test: tests
	-./$(TEST_EXECUTABLE) ||:

clean:
	rm -f $(EXECUTABLE)
	rm -f *.o
	rm -f *.dwo

cleantests:
	rm -f $(TEST_EXECUTABLE)
	rm -f tests/*.o
	rm -f tests/*.dwo

cleanall: clean cleantests
