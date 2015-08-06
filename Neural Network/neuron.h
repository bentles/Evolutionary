#ifndef NEURON_H
#define NERUON_H
#include <vector>
#include <stdlib.h>
#include "func.h"

typedef std::vector<double> row_t;

namespace nnet
{
    class Neuron {
    private:
        row_t m_weights;
        row_t m_inputs;
        int m_size;
        IFunc& m_function;

        double getNet();
    public:
        double getInput(int index);
        Neuron(int s, IFunc* function);        
        void Print();
        void setWeight(int index, double value);
        void addWeight(int index, double value);
        void setInput(int index, double value);
        double getOutput();
        void randomizeWeights();
    };
}
#endif /* NERUON_H */
