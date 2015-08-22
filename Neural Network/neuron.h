#ifndef NEURON_H
#define NERUON_H
#include <vector>
#include <stdlib.h>
#include "helpers.h"
#include "func.h"

typedef std::vector<double> row_t;

namespace nnet
{
    class Neuron {
    private:
        std::vector<KahanAccumulation> m_weights;
        row_t m_inputs;
        int m_size;
        Func& m_function;

        double getNet();
    public:
        double getInput(int index);
        Neuron(int s, Func* function);        
        void printWeights();
        void setWeight(int index, double value);
        void addWeight(int index, double value);
        void setInput(int index, double value);
        void initBiasInput(double value);
        double getOutput();
        void randomizeWeights();
    };
}
#endif /* NERUON_H */
