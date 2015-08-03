#include <iostream>
#include <vector>
#include <cassert>
#include "neuron.h"

namespace nnet {
    //doing this reminds me of javascript Foo.prototype.bar = function(){}; for some reason
    Neuron::Neuron(int size, IFunc* function) : m_function(*function), m_size(size) {
        for(int i = 0; i < size; i++) {
            m_weights.push_back(0.0f);
            m_inputs.push_back(0.0f);
        }
    }

    void Neuron::SetWeight(int index, float value)
    {
        assert(index >= 0 && index < m_size);
        m_weights[index] = value;
    }

    void Neuron::Print() {
        std::cout << m_size << std::endl;  
        for(int i = 0; i < m_size; i++) {
            std::cout << m_weights[i] << ":" << m_inputs[i] << std::endl;  
        }
    }

    float Neuron::GetNet() {
        return 0.0f;
    }

    float Neuron::GetOutput() {
        return m_function.apply(GetNet());
    }
}
