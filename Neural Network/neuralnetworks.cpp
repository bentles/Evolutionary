#include "neuralnetworks.h"

namespace nnet
{
    StandardFFNN::StandardFFNN(Func &input_func,
                               int nr_inputs,
                               Func &hidden_func,
                               int nr_hiddens,
                               Func &output_func,
                               int nr_outputs,                               
                               const DataResultsSet &training,
                               const DataResultsSet &verification) :
        m_training(training),
        m_verification(verification),
        m_learn_rate(0.0001),
        m_momentum(0)
    {
        //create layers
        for (int i = 0; i < nr_inputs; i++) {
            m_input_layer.push_back(Neuron(1, input_func));
        }

        for (int i = 0; i < nr_hiddens; i++) {
            m_hidden_layer.push_back(Neuron(nr_inputs, hidden_func));
        }

        for (int i = 0; i < nr_outputs; i++) {
            m_output_layer.push_back(Neuron(nr_hiddens, output_func));
        }
    }
    

    vector<double> StandardFFNN::getOutputs(int pattern) {
        //need as many outputs as there are output neurons
        vector<double> outputs(m_output_layer.size());

        //put input into input layer
        for(int i = 0; i < m_input_layer.size(); i++) {
            m_input_layer[i].setInput(0, m_training.getPattern(pattern)[i]);
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

    void StandardFFNN::updateWeightsStochastic(int pattern) {
        getOutputs(pattern);
        //deltaO_k = (t_k - o_k) * f'(o_k0)
        vector<double> deltaO_k;
        for(int k = 0; k < m_output_layer.size(); k++) {
            deltaO_k.push_back(
                -(m_training.getOutputs(pattern)[k] - m_output_layer[k].getOutput()) *
                m_output_layer[k].getOutput(1)) ;
        }

        //get weight updates for hidden to output
        vector<vector<double> > DeltaW_kj;
        for (int k = 0; k < m_output_layer.size(); k++) {
            vector<double> dubvect;
            for (int j = 0; j < m_hidden_layer.size(); j++) {                
                dubvect.push_back(-m_learn_rate *
                                     m_hidden_layer[j].getOutput() *
                                     deltaO_k[k]);
            }
            DeltaW_kj.push_back(dubvect);
        }

        //deltaY_j = 
        vector<double> deltaY_j;
        for (int j = 0; j < m_hidden_layer.size(); j++) {
            double sum = 0;
            for (int k = 0; k < m_output_layer.size(); k++) {
                sum += deltaO_k[k] *
                    m_output_layer[k].getWeight(j) *
                    m_hidden_layer[j].getOutput(1);
            }
            deltaY_j.push_back(sum);
        }
        
        //get weight updates for input to hidden
        vector<vector<double> > DeltaV_ji;
        for (int j = 0; j < m_hidden_layer.size(); j++) {
            vector<double> dubvect;
            for (int i = 0; i < m_input_layer.size(); i++) {                
                dubvect.push_back(-m_learn_rate *
                                  deltaY_j[j] *
                                  m_input_layer[i].getOutput());
            }
            DeltaV_ji.push_back(dubvect);
        }
        
        //apply weight updates
        //====================
        //weights on outputs (from hidden to output) DeltaW_kj
        for (int k = 0; k < m_output_layer.size(); k++) {
            for (int j = 0; j < m_hidden_layer.size(); j++) {
                m_output_layer[k].addWeight(j, DeltaW_kj[k][j], m_momentum);
            }
        }

        //weights on hiddens (from input to hidden) DeltaV_ji
        for (int j = 0; j < m_output_layer.size(); j++) {
            for (int i = 0; i < m_hidden_layer.size(); i++) {
                m_output_layer[j].addWeight(i, DeltaV_ji[j][i], m_momentum);
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

    void StandardFFNN::setLearnRate(double rate) {
        m_learn_rate = rate;
    }

    void StandardFFNN::setMomentum(double momentum) {
        m_momentum = momentum;
    }
   
    void StandardFFNN::trainFor(int iterations) {
        std::cout << m_training.size() << std::endl;
        for (int i = 0; i < iterations; i++) {
            for (int k = 0; k < m_training.size(); k++) {
                updateWeightsStochastic(k);
                //std::cout << k << std::endl;
            }
        }
    }
}
