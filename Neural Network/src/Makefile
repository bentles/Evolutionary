CFLAGS = -g -std=c++11

all: neuron.cpp functions.cpp neurIO.cpp helpers.cpp neuralnetworks.cpp
	g++ $(CFLAGS) -c neuron.cpp functions.cpp neurIO.cpp helpers.cpp neuralnetworks.cpp
	ar rvs libnnet.a neuron.o   functions.o   neurIO.o   helpers.o   neuralnetworks.o

test: all
	g++ $(CFLAGS) test.cpp libnnet.a -o testacious
