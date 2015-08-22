#include "neuralnetworks.h"

namespace nnet
{
    StandardFFNN::StandardFFNN(vector<Neuron> input_layer,
                     vector<Neuron> hidden_layer,
                     vector<Neuron> output_layer,
                               DataSet training, DataSet verification, DataSet testing) {
        m_input_layer = input_layer;
        m_hidden_layer =  hidden_layer;
        m_output_layer =  output_layer;
        m_training = training;
        m_verification = verification;
        m_testing = testing;        
    }

    vector<double> getOutputs(const vector<double> &pattern)
    {
        //need as many outputs as there are output neurons
        vector<double> outputs(m_output_layer.size());

        //put input into input layer
        for(int i = 0; i < input_layer.size(); i++) {
            m_input_layer[i].setInput(0, pattern[i]);
        }

        //set hidden inputs from input outputs
        for(int i = 0; i < m_hidden_layer.size(); i++) {
            for (int j = 0; j < m_input_layer.size(); j++) {
                m_hidden_layer[i].setInput(j, m_input_layer[j].getOutput());
            }
        }

        //set output inputs from hidden outputs
        for(int i = 0; i < m_output_layer.size(); i++) {
            for (int j = 0; j < m_hidden_layer.size(); j++) {
                m_output_layer[i].setInput(j, m_hidden_layer[j].getOutput());
            }
        }

        //get outputs
        for (i = 0; i < m_output_layer.size(); i++) {
            outputs[i] = m_output_layer[i].getOutput();
        }

        return outputs;
    }

}
