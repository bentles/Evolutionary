#include <iostream>
#include "neuron.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    using namespace nnet;
    Sigmoid* sig;
    Neuron test(12, sig);
    test.SetWeight(0, 0.1f);
    test.Print();
    return 0;
}
