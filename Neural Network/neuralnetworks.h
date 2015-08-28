#ifndef NEURAL_NETWORKS_H
#define NEURAL_NETWORKS_H

#include <vector>
#include <math.h>
#include "neurIO.h"
#include "neuron.h"

using std::vector;

namespace nnet
{
    class StandardFFNN
    {
    private:        
        vector<Neuron> m_input_layer;
        vector<Neuron> m_hidden_layer;
        vector<Neuron> m_output_layer;
        DataResultsSet m_training;
        DataResultsSet m_verification;
        DataSet m_testing;
    public:
        // the idea is to have this take in vectors of customly created layers
        // though i guess some assumptions may have to be made about these vectors
        // for training
        // TODO:do all elems of a vector need the same activation fn??
        StandardFFNN(vector<Neuron> input_layer,
                     vector<Neuron> hidden_layer,
                     vector<Neuron> output_layer,
                     const DataResultsSet &training,
                     const DataResultsSet &verification,
                     const DataSet &test);

        vector<double> getOutputs(const vector<double> &pattern);
        void updateWeightsStochastic(int pattern, double learn_rate, double momentum);
        double getSSE(int pattern);
    };
}

#endif /* NEURAL_NETWORKS_H */
