CFLAGS = -g -std=c++11
CHK_SOURCES = neuron.cpp functions.cpp neurIO.cpp helpers.cpp neuralnetworks.cpp

all: neuron.cpp
	g++ $(CFLAGS) -c neuron.cpp functions.cpp neurIO.cpp helpers.cpp neuralnetworks.cpp
	ar rvs libnnet.a neuron.o functions.o neurIO.o helpers.o neuralnetworks.o

test: all
	g++ $(CFLAGS) test.cpp libnnet.a -o testacious
