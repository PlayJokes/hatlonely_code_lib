CXX=c++
CXXFLAGS=-g -Wall

target: graph
graph: graph.o graph_test.o 
	$(CXX) -o $@ $?

graph.o: graph.cpp graph.h
graph_test.o: graph_test.cpp graph.h

.PHONY: clean
clean:
	rm *.o
	rm graph
