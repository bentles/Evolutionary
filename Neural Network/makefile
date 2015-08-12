CFLAGS = -g -std=c++11

all: neuron.cpp
	g++ $(CFLAGS) -c neuron.cpp functions.cpp neurIO.cpp helpers.cpp
	ar rvs libnnet.a neuron.o functions.o neurIO.o helpers.o

test: all
	g++ $(CFLAGS) test.cpp libnnet.a -o testacious
