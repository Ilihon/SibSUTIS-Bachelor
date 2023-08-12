DIR_BIN = ./bin
DIR_BUILD = ./build
DIR_SRC = ./src
DIR_TEST = ./build/test
DIR_T = ./test

all: $(DIR_BIN)/main

$(DIR_BIN)/main: $(DIR_BUILD)/main.o $(DIR_BUILD)/course.o
	g++ -Wall -o $(DIR_BIN)/main $(DIR_BUILD)/main.o $(DIR_BUILD)/course.o
$(DIR_BUILD)/main.o: $(DIR_SRC)/main.cpp
	g++ -Wall -Werror -o $(DIR_BUILD)/main.o -c $(DIR_SRC)/main.cpp 
$(DIR_BUILD)/course.o: $(DIR_SRC)/course.cpp
	g++ -Wall -Werror -o $(DIR_BUILD)/course.o -c $(DIR_SRC)/course.cpp

.PHONY: clean test

$(DIR_BIN)/testing: $(DIR_TEST)/coursetest.o $(DIR_TEST)/course.o
	g++ -o $(DIR_BIN)/testing $(DIR_TEST)/coursetest.o $(DIR_TEST)/course.o -std=c++11
$(DIR_TEST)/coursetest.o: $(DIR_T)/coursetest.cpp
	g++ -o $(DIR_TEST)/coursetest.o -c $(DIR_T)/coursetest.cpp -std=c++11
$(DIR_TEST)/course.o: $(DIR_SRC)/course.cpp
	g++ -o $(DIR_TEST)/course.o -c $(DIR_SRC)/course.cpp -std=c++11

test: $(DIR_BIN)/testing

clean:
	rm -f $(DIR_BIN)/main
	rm -f $(DIR_BIN)/testing
	rm -f $(DIR_BUILD)/*.o
	rm -f $(DIR_TEST)/*.o