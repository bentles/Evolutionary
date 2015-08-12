#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"
#include "helpers.h"
#include <math.h>

int main(int argc, char *argv[])
{
    //this is all very messy until i need to generalise things for assignment 2
    
    using namespace nnet;
    string a = "../Assignment 1/SalTraining.csv";
    vector< vector<double> > data = getDataCsv(a);
    int neuron_size = data.size() - 1;
    
    Linear lin;
    Neuron priceNeuron(neuron_size, &lin);

    std::cout << "randomising weights..." << std::endl;
    priceNeuron.randomizeWeights();

    double zeta = 0.00000001;

    int data_size = data[0].size();

    for(int l = 0; l < 400000; l++)
    {
        //re-init the vector of updates
        vector<KahanAccumulation> updates(neuron_size + 1);
        

        //go through every pattern
        for(int i = 0; i < data_size; i++) {
            
            //set all inputs for pattern 
            for (int j = 1; j <= neuron_size; j++) {
                priceNeuron.setInput(j, data[j][i]);
            }

            //sum up updates
            for (int j = 0; j <= neuron_size; j++) {
                updates[j] = KahanSum(updates[j], zeta*2*(data[0][i] -
                                                priceNeuron.getOutput())*priceNeuron.getInput(j));
            }
        }

        std::cout << "Iteration: " << l << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << updates[i].sum << ((i==7)?"":",");
        }
        std::cout << std::endl;
        
        //apply updates
        for (int j = 0; j <= neuron_size; j++) {
            priceNeuron.addWeight(j, updates[j].sum);
        }
    }
    priceNeuron.Print();
    
    return 0;
}
