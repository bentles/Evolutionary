#include <iostream>
#include <vector>
#include <cassert>
#include "neuron.h"

namespace nnet {
    //size includes bias;com
    Neuron::Neuron(int size, IFunc* function) : m_function(*function), m_size(size) {
        //bias
        m_weights.push_back(1.0f);
        m_inputs.push_back(0.0f);
        
        for(int i = 1; i < size; i++) {
            m_weights.push_back(0.0f);
            m_inputs.push_back(0.0f);
        }
    }

    void Neuron::SetInput(int index, float value)
    {
        assert(index >= 0 && index < m_size);
        m_inputs[index] = value;
    }

    void Neuron::SetWeight(int index, float value)
    {
        assert(index >= 0 && index < m_size);
        m_weights[index] = value;
    }

    void Neuron::AddWeight(int index, float value)
    {
        assert(index >= 0 && index < m_size);
        m_weights[index] += value;
    }

    void Neuron::Print() {
        std::cout << m_size << std::endl;  
        for(int i = 0; i < m_size; i++) {
            std::cout << m_weights[i] << ":" << m_inputs[i] << std::endl;  
        }
    }

    float Neuron::GetNet() {
        float acc;
        for (int i = 0; i < m_size; i++) {
            acc += m_weights[i]*m_inputs[i];
        }
        
        return acc;
    }

    float Neuron::GetOutput() {
        return m_function.apply(GetNet());
    }
}
