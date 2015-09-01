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
                               const DataResultsSet &verification,
                               const DataSet &test) :
        m_training(training),
        m_verification(verification),
        m_test(test),
        m_learn_rate(0.0001),
        m_momentum(0),
        m_verbose(false)
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

    StandardFFNN::StandardFFNN(Func &input_func,
                               int nr_inputs,
                               vector<Neuron> hidden,
                               Func &output_func,
                               int nr_outputs,                               
                               const DataResultsSet &training,
                               const DataResultsSet &verification,
                               const DataSet &test) :
        m_hidden_layer(hidden),
        m_training(training),
        m_test(test),
        m_verification(verification),
        m_learn_rate(0.0001),
        m_momentum(0),
        m_verbose(false)
    {
        //create layers
        for (int i = 0; i < nr_inputs; i++) {
            m_input_layer.push_back(Neuron(1, input_func));
        }

        for (int i = 0; i < nr_outputs; i++) {
            m_output_layer.push_back(Neuron(hidden.size(), output_func));
        }
    }

    vector<double> StandardFFNN::getOutputs(int pattern, int set) {
        //TODO: this is super slow
        // make each neuron take a list of other neurons for input perhaps
        
        //need as many outputs as there are output neurons
        vector<double> outputs(m_output_layer.size());

        assert(set >= 0 && set <= 2);
            //put input into input layer
        for(int i = 0; i < m_input_layer.size(); i++) {
            double value = 0;
            if (set == 0)
                value = m_training.getPattern(pattern)[i];
            else if (set == 1)
                value = m_verification.getPattern(pattern)[i];
            else
                value = m_test.getPattern(pattern)[i];
                
            m_input_layer[i].setInput(0, value);
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
        //output gradients: deltaO_k = (t_k - o_k) * f'(o_k0)
        vector<double> deltaO_k;
        for(int k = 0; k < m_output_layer.size(); k++) {
            deltaO_k.push_back(
                -(m_training.getOutputs(pattern)[k] - m_output_layer[k].getOutput()) *
                m_output_layer[k].getOutput(1)) ;
        }

        //Hidden gradients: deltaY_j = 
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

        //get and apply weight updates for hidden to output
        for (int k = 0; k < m_output_layer.size(); k++) {
            for (int j = 0; j < m_hidden_layer.size(); j++) {
                double update = -m_learn_rate *
                                     m_hidden_layer[j].getOutput() *
                                     deltaO_k[k];
                m_output_layer[k].addWeight(j, update, m_momentum);
            }
        }
        
        //get and apply weight updates for input to hidden
        for (int j = 0; j < m_hidden_layer.size(); j++) {
            for (int i = 0; i < m_input_layer.size(); i++) {                
                double update = -m_learn_rate *
                                  deltaY_j[j] *
                                  m_input_layer[i].getOutput();
                m_hidden_layer[j].addWeight(i, update, m_momentum);
            }
        }

        //learned how to update bias weights from:
        //https://visualstudiomagazine.com/Articles/2013/08/01/Neural-Network-Back-Propagation-Using-C.aspx?Page=3
        
        for (int i = 0; i < m_hidden_layer.size(); ++i)
        {
            double delta = m_learn_rate * deltaY_j[i] * 1.0; 
            m_hidden_layer[i].addBiasWeight(delta, m_momentum);
        }

        for (int i = 0; i < m_output_layer.size(); ++i)
        {
            double delta = m_learn_rate * deltaO_k[i] * 1.0;
             m_output_layer[i].addBiasWeight(delta, m_momentum);
        }
        
    }

    //TODO: RENAME ME!!
    double StandardFFNN::getSSE(int pattern, int set)
    {
        double acc = 0;
        assert(set == 0 || set == 1);
        for (int k = 0; k < m_output_layer.size(); k++) {
            double output = (set == 0)? m_training.getOutputs(pattern)[k] : m_verification.getOutputs(pattern)[k];            
            acc += pow(output - m_output_layer[k].getOutput(), 2);
        }
        

        acc /= m_output_layer.size();
    }

    StandardFFNN& StandardFFNN::setLearnRate(double rate) {
        m_learn_rate = rate;
        return *this;
    }

    StandardFFNN& StandardFFNN::setMomentum(double momentum) {
        m_momentum = momentum;
        return *this;
    }
   
    StandardFFNN& StandardFFNN::trainFor(int iterations) {       
        for (int i = 0; i < iterations; i++) {
            m_learn_rate *= 0.998;
            m_training.shuffle();
            double sse_sum = 0;
            double v_sse_sum = 0;
            for (int k = 0; k < m_training.size(); k++) {
                updateWeightsStochastic(k);
                sse_sum += getSSE(k);
            }

            for (int k = 0; k < m_verification.size(); k++) {
                getOutputs(k, 1); //verification set is 1
                v_sse_sum += getSSE(k);
            }
            
            if (m_verbose) {
//                std::cout << "iteration " << i << ": " << std::endl;
                std::cout << sse_sum/m_training.size() << "," << sse_sum/m_verification.size() << std::endl;
                //              std::cout << "VMSE: " <<  << std::endl;
                //               std::cout << "LR: " << m_learn_rate << std::endl;
            }     
        }

        std::cout << "test data:" << std::endl;
        if(m_verbose)
        {
            for (int k = 0; k < m_test.size(); k++) {
                vector<double> outp =  getOutputs(k, 2);
                int j = 0;
                for (; j < outp.size() - 1; j++) {
                      std::cout << outp[j] << ", " ;
                }
                std::cout << outp[j] << std::endl;
            }

        }
        
        return *this;
    }

    StandardFFNN& StandardFFNN::printOutputs()
    {
        for (int i = 0; i < m_training.size(); i++) {
            int j = 0;            
            for (; j < m_output_layer.size() - 1; j++) {
                std::cout << getOutputs(i)[j] << ", " ;
            }
            std::cout << getOutputs(i)[j] << std::endl;
        }
        return *this;
    }

    StandardFFNN& StandardFFNN::setTrainingSet(DataResultsSet train_set)
    {
        m_training = train_set;
        return *this;
    }

    StandardFFNN& StandardFFNN::verbose(bool verbose)
    {
        m_verbose = verbose;
        return *this;
    }
}
