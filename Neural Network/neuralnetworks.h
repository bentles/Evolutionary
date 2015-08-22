#include <vector>
#include "neuron.h"

#ifndef NEURAL_NETWORKS_H
#define NEURAL_NETWORKS_H

namespace nnet
{
    class StandardFFNN
    {
    private:        
        vector<Neuron> m_input_layer;
        vector<Neuron> m_hidden_layer;
        vector<Neuron> m_output_layer;
        DataSet m_training;
        DataSet m_verification;
        DataSet m_testing;
    public:
        // the idea is to have this take in vectors of customly created layers
        // though i guess some assumptions may have to be made about these vectors
        // for training
        // TODO:do all elems of a vector need the same activation fn??
        StandardFFNN(vector<Neuron> input_layer,
                     vector<Neuron> hidden_layer,
                     vector<Neuron> output_layer,
                     DataSet training, DataSet verification, DataSet test);

        vector<double> getOutputs();
}

#endif /* NEURAL_NETWORKS_H */
