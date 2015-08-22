#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "neuron.h"

namespace nnet {
    //size excludes bias
    Neuron::Neuron(int size, Func* function) : m_function(*function), m_size(size + 1) {
        for(int i = 0; i < m_size; i++) {
            m_weights.push_back({0});
            m_inputs.push_back(0);
        }        
        //bias
        m_weights.push_back({0});
        m_inputs.push_back(-1);
    }

    void Neuron::setInput(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_inputs[index] = value;
    }

    //we will not modify the pattern given
    void Neuron::setInputs(const vector<double>& pattern) {
        for(int i = 0; i < pattern.size(); i++) {
            setInput(i, pattern[i]);
        }
    }

    double Neuron::getInput(int index) {
        return m_inputs[index];
    }

    void Neuron::initBiasInput(double value){ //default is -1 to match text
        m_inputs[m_size] = value;
    }

    void Neuron::setWeight(int index, double value) {
        assert(index >= 0 && index <= m_size); //can set bias weight
        m_weights[index].sum = value;
    }

    void Neuron::addWeight(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_weights[index] = KahanSum(m_weights[index], value);
    }

    void Neuron::printWeights() {
        std::cout << m_size << std::endl;  
        for(int i = 0; i < m_size; i++) {
            std::cout << m_weights[i].sum << ", ";
        }
        std::cout << m_weights[m_size] << std::endl;
    }

    double Neuron::getNet() {
        double acc;
        for (int i = 0; i < m_size; i++) {
            acc += m_weights[i].sum*m_inputs[i];
        }        
        return acc;
    }

    double Neuron::getOutput() {
        return m_function.apply(getNet());
    }

    void Neuron::randomizeWeights() {
        for (int i = 1; i < m_size; i++) {
            m_weights[i].correction = 0;
            m_weights[i].sum = ((double) rand() / (RAND_MAX))/ 10; //want these to be small
        }
    }
}
