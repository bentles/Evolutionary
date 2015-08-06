#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"
#include <math.h>

int main(int argc, char *argv[])
{
    using namespace nnet;
    string a = "../Assignment 1/SalData.csv";
    vector< vector<double> > data = getDataCsv(a);
    int neuron_size = data.size() - 1;
    
    Linear lin;
    Neuron priceNeuron(neuron_size, &lin);

    std::cout << "randomising weights..." << std::endl;
    priceNeuron.randomizeWeights();

    double zeta = 0.00000000000000001;

    int data_size = data[0].size();
    vector<double> updates(neuron_size);

    for(int l = 0; l < 100000; l++)
    {
        std::cout << l << std::endl;
        for(int i = 0; i < data_size; i++) {
            for (int j = 1; j <= neuron_size; j++) {
                priceNeuron.setInput(j, data[j][i]);
            }

            for (int j = 1; j <= neuron_size; j++) {
                updates[j-1] += zeta*2*(data[0][i] -
                                        priceNeuron.getOutput())*priceNeuron.getInput(j);
            }
        }

        std::cout << updates[0] << std::endl;
        for (int j = 1; j <= neuron_size; j++) {
            priceNeuron.addWeight(j, updates[j-1]);
        }
    }
    priceNeuron.Print();
    
    return 0;
}
