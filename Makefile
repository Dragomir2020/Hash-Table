CC=g++
CFLAGS=-v -c -std=c++11 -Wall -ggdb -I. --coverage -O0
LDFLAGS=-std=c++11 --coverage
SOURCES=hashsandbox.cpp 
EXECUTABLE=hash
TESTS=HashTable_test.h
TESTSOURCES=HashTable_test.h


OBJECTS=$(SOURCES:.cpp=.o)

FLAGS   = -Iinclude

all: $(SOURCES) $(EXECUTABLE)
	
# These next lines do a bit of magic found from http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# Essentially it asks the compiler to read the .cpp files and generate the needed .h dependencies.
# This way if any .h file changes the correct .cpp files will be recompiled
depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
# End .h file magic

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
	rm -f ./.depend
	rm -f testrunner*
	rm -f labtestrunner*
	
# CXX Testing	
#CXXLOCATION = /Users/dillondragomir/Data_structures/dragomdv/Lab7/cxxtest
CXXLOCATION = cxxtest
CXXTESTGEN = $(CXXLOCATION)/bin/cxxtestgen

test: testrunner
	./testrunner

testrunner: testrunner.cpp 
	g++ -v --coverage -O0 -I. -std=c++11 -ggdb -I$(CXXLOCATION)/ -o testrunner testrunner.cpp
	

testrunner.cpp: $(HEADERS) $(TESTSOURCES) 
	$(CXXTESTGEN) --error-printer -o testrunner.cpp $(TESTS)
	

