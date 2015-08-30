#ifndef NEURAL_NETWORKS_H
#define NEURAL_NETWORKS_H

#include <vector>
#include <math.h>
#include "neurIO.h"
#include "neuron.h"
#include "functions.h"

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
        double m_learn_rate;
        double m_momentum;

        void updateWeightsStochastic(int pattern);
    public:
        // the idea is to have this take in vectors of customly created layers
        // though i guess some assumptions may have to be made about these vectors
        // for training
        // TODO:do all elems of a vector need the same activation fn??
        StandardFFNN(Func &input_func,
                               int nr_inputs,
                               Func &hidden_func,
                               int nr_hiddens,
                               Func &output_func,
                               int nr_outputs,                               
                               const DataResultsSet &training,
                               const DataResultsSet &verification);

        vector<double> getOutputs(int pattern);
        double getSSE(int pattern);
        StandardFFNN& setLearnRate(double rate);
        StandardFFNN& setMomentum(double momentum);
        StandardFFNN& trainFor(int iterations);
    };
}

#endif /* NEURAL_NETWORKS_H */
