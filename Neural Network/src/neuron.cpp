#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "neuron.h"

namespace nnet {
    //size excludes bias
    Neuron::Neuron(int size, Func& function) :
        m_function(function),
        m_size(size),
        m_valid(false),
        m_prev_delta_w(0) {
        
        for(int i = 0; i < size; i++) {
            m_weights.push_back({0});
            m_prev_delta_w.push_back(0);
            
            m_inputs.push_back(0);
        }        
        //bias
        m_weights.push_back({0});
        m_prev_delta_w.push_back(0);
        
        m_inputs.push_back(-1);

        //randomise weights
        randomizeWeights();
    }

    void Neuron::setInput(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_inputs[index] = value;

        m_valid = false;
    }

    //we will not modify the pattern given
    void Neuron::setInputs(const vector<double> &pattern) {
        for(int i = 0; i < pattern.size(); i++) {
            setInput(i, pattern[i]);
        }

        m_valid = false;
    }

    double Neuron::getInput(int index) {
        return m_inputs[index];
    }

    double Neuron::getWeight(int i) {
        return m_weights[i].sum;
    }

    void Neuron::initBiasInput(double value){ //default is -1 to match text
        m_inputs[m_size] = value;

        m_valid = false;
    }

    void Neuron::setWeight(int index, double value) {
        assert(index >= 0 && index <= m_size); //can set bias weight
        m_weights[index].sum = value;

        m_valid = false;
    }

    void Neuron::addWeight(int i, double value, double momentum) {
        assert(i >= 0 && i <= m_size); //can add bias weight
        //momentum term built into neuron
        m_weights[i] = KahanSum(m_weights[i], value + momentum * m_prev_delta_w[i]);
        //save last weight update
        m_prev_delta_w[i] = value;
        m_valid = false;
    }
    
    void Neuron::addBiasWeight(double value, double momentum)
    {
        addWeight(m_size, value, momentum);
    }

    void Neuron::printWeights() {
        std::cout << m_size << std::endl;  
        for(int i = 0; i < m_size; i++) {
            std::cout << m_weights[i].sum << ", ";
        }
        std::cout << m_weights[m_size].sum << std::endl;
    }

    double Neuron::getNet() {
        if (!m_valid)
        {        
            double acc;
            for (int i = 0; i <= m_size; i++) {
                acc += m_weights[i].sum*m_inputs[i];
            }
            //cache last value of this function
            m_net = acc;
            //keep track of the validity of cached value
            m_valid = true;
            return acc;
        }
        else
            return m_net;
    }

    double Neuron::getOutput(int deriv) {
            return m_function.apply(getNet(), deriv);        
    }

    void Neuron::randomizeWeights() {
        for (int i = 0; i <= m_size; i++) {
            m_weights[i].correction = 0;
            m_weights[i].sum = ((double) rand() / (RAND_MAX))/ 10; //want these to be small
        }
    }
}
