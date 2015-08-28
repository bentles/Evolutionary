#include "neuralnetworks.h"

namespace nnet
{
    StandardFFNN::StandardFFNN(vector<Neuron> input_layer,
                               vector<Neuron> hidden_layer,
                               vector<Neuron> output_layer,
                               const DataResultsSet &training,
                               const DataResultsSet &verification,
                               const DataSet &testing) :
        m_input_layer(input_layer),
        m_hidden_layer(hidden_layer),
        m_output_layer(output_layer),
        m_training(training),
        m_verification(verification),
        m_testing(testing) {}
    

    vector<double> StandardFFNN::getOutputs(const vector<double> &pattern) {
        //need as many outputs as there are output neurons
        vector<double> outputs(m_output_layer.size());

        //put input into input layer
        for(int i = 0; i < m_input_layer.size(); i++) {
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
        for (int i = 0; i < m_output_layer.size(); i++) {
            outputs[i] = m_output_layer[i].getOutput();
        }

        return outputs;
    }

    void StandardFFNN::updateWeightsStochastic(int pattern,
                                               double learn_rate,
                                               double momentum) {
        //deltaO_k = (t_k - o_k) * f'(o_k0)
        vector<double> deltaO_k;
        for(int i = 0; i < m_output_layer.size(); i++) {
            deltaO_k.push_back(
                -(m_training.getOutputs(pattern)[i] - m_output_layer[i].getOutput()) *
                m_output_layer[i].getOutput(1)) ;
        }

        //get weight updates for hidden to output
        vector<vector<double> > DeltaW_kj;
        for (int k = 0; k < m_output_layer.size(); k++) {
            vector<double> dubvect;
            DeltaW_kj.push_back(dubvect);
            for (int j = 0; j < m_hidden_layer.size(); j++) {                
                dubvect.push_back(-learn_rate *
                                     m_hidden_layer[j].getOutput() *
                                     deltaO_k[k]);
            }
        }

        //deltaY_j = 
        vector<double> deltaY_j;
        for (int j = 0; j < m_hidden_layer.size(); j++) {
            for (int k = 0; k < m_output_layer.size(); k++) {
                deltaY_j.push_back(deltaO_k[k] *
                                   m_output_layer[k].getWeight(j) *
                                   m_hidden_layer[j].getOutput(1));
            }
        }
        
        //get weight updates for input to hidden
        vector<vector<double> > DeltaV_ji;
        for (int j = 0; j < m_output_layer.size(); j++) {
            vector<double> dubvect;
            DeltaV_ji.push_back(dubvect);
            for (int i = 0; i < m_hidden_layer.size(); i++) {                
                dubvect.push_back(-learn_rate *
                                  deltaY_j[j] *
                                  m_input_layer[i].getOutput());
            }
        }
        
        //apply weight updates
        //====================
        //weights on outputs (from hidden to output) DeltaW_kj
        for (int k = 0; k < m_output_layer.size(); k++) {
            for (int j = 0; j < m_hidden_layer.size(); j++) {
                m_output_layer[k].addWeight(j, DeltaW_kj[k][j], momentum);
            }
        }

        //weights on hiddens (from input to hidden) DeltaV_ji
        for (int j = 0; j < m_output_layer.size(); j++) {
            for (int i = 0; i < m_hidden_layer.size(); i++) {
                m_output_layer[j].addWeight(i, DeltaV_ji[j][i], momentum);
            }
        }
    }

    double StandardFFNN::getSSE(int pattern)
    {
        double acc = 0;
        for (int k = 0; k < m_output_layer.size(); k++) {
            acc += pow(m_training.getOutputs(pattern)[k] - m_output_layer[k].getOutput(), 2);
        }

        acc /= m_output_layer.size();
    }   
}
