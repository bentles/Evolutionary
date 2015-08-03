#ifndef NEURON_H
#define NERUON_H
#include <vector>
#include "func.h"

typedef std::vector<float> row_t;

namespace nnet
{
    class Neuron {
    private:
        row_t m_weights;
        row_t m_inputs;
        int m_size;
        IFunc& m_function;

        float GetNet();
    public:
        Neuron(int s, IFunc* function);        
        void Print();
        void SetWeight(int index, float value);
        float GetOutput();
    };
}
#endif /* NERUON_H */
