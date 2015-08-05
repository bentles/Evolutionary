all: neuron.cpp
	g++ -g -c neuron.cpp functions.cpp neurIO.cpp
	ar rvs libnnet.a neuron.o functions.o

test: all
	g++ -g test.cpp libnnet.a -o testacious
