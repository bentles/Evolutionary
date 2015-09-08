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
        vector<Neuron> m_output_layer;
        vector<Neuron> m_hidden_layer; 
        DataResultsSet m_training;
        DataResultsSet m_verification;
        DataSet m_test;
        double m_learn_rate;
        double m_momentum;
        bool m_verbose;

        void updateWeightsStochastic(int pattern);
    public:
        StandardFFNN(Func &input_func,
                     int nr_inputs,
                     Func &hidden_func,
                     int nr_hiddens,
                     Func &output_func,
                     int nr_outputs,                               
                     const DataResultsSet &training,
                     const DataResultsSet &verification,
                     const DataSet &test);

        StandardFFNN(Func &input_func,
                     int nr_inputs,
                     vector<Neuron> hidden,
                     Func &output_func,
                     int nr_outputs,                               
                     const DataResultsSet &training,
                     const DataResultsSet &verification,
                     const DataSet &test);

        vector<double> getOutputs(int pattern, int set = 0);
        double getSSE(int pattern, int set = 0);
        StandardFFNN& setLearnRate(double rate);
        StandardFFNN& setMomentum(double momentum);
        StandardFFNN& trainFor(int iterations);
        StandardFFNN& printOutputs();
        StandardFFNN& setTrainingSet(DataResultsSet train_set);
        StandardFFNN& verbose(bool verbose);
    };
}

#endif /* NEURAL_NETWORKS_H */
