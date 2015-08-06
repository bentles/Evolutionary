#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "neuron.h"

namespace nnet {
    //size excludes bias
    Neuron::Neuron(int size, IFunc* function) : m_function(*function), m_size(size + 1) {
        //bias
        m_weights.push_back(1.0f);
        m_inputs.push_back(0.0f);
        
        for(int i = 1; i < m_size; i++) {
            m_weights.push_back(0.0f);
            m_inputs.push_back(0.0f);
        }
    }

    void Neuron::setInput(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_inputs[index] = value;
    }

    double Neuron::getInput(int index) {
        return m_inputs[index];
    }

    void Neuron::setWeight(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_weights[index] = value;
    }

    void Neuron::addWeight(int index, double value) {
        assert(index >= 0 && index < m_size);
        m_weights[index] += value;
    }

    void Neuron::Print() {
        std::cout << m_size << std::endl;  
        for(int i = 0; i < m_size; i++) {
            std::cout << m_weights[i] << ":" << m_inputs[i] << std::endl;  
        }
    }

    double Neuron::getNet() {
        double acc;
        for (int i = 0; i < m_size; i++) {
            acc += m_weights[i]*m_inputs[i];
        }        
        return acc;
    }

    double Neuron::getOutput() {
        return m_function.apply(getNet());
    }

    void Neuron::randomizeWeights() {
        for (int i = 1; i < m_size; i++) {
            m_weights[i] = ((double) rand() / (RAND_MAX));
        }
    }
}
