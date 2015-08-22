#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"
#include "helpers.h"
#include <math.h>

int main(int argc, char *argv[])
{
    
    using namespace nnet;
    string a = "../Assignment 1/SalTraining.csv";
    vector< vector<double> > data = getDataCsv(a);
    int neuron_size = data.size() - 1;
    
    Linear lin;
    Neuron priceNeuron(neuron_size, &lin);
    
    return 0;
}
