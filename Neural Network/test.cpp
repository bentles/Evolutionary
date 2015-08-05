#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"

int main(int argc, char *argv[])
{
    using namespace nnet;
    Sigmoid* sig;
    Neuron test(12, sig);
    test.SetWeight(0, 0.1f);
    test.Print();
    string a = "../Assignment 1/SalData.csv";
    vector<vector<float> > data = getDataCsv(a);
    printData(data);
    
    return 0;
}
