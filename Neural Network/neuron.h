#ifndef NEURON_H
#define NERUON_H

#include <vector>
#include <stdlib.h>
#include "helpers.h"
#include "func.h"

using std::vector;

typedef std::vector<double> row_t;

namespace nnet
{
    class Neuron {
    private:
        std::vector<KahanAccumulation> m_weights;
        row_t m_inputs;
        double m_net;
        double m_prev_delta_w;
        bool m_valid;
        int m_size;
        Func& m_function;

        double getNet();
    public:
        double getInput(int index);
        double getWeight(int index);
        Neuron(int s, Func* function);        
        void printWeights();
        void setWeight(int index, double value);
        void addWeight(int index, double value, double momentum = 0);
        void setInput(int index, double value);
        void setInputs(const vector<double> &pattern);
        void initBiasInput(double value);
        double getOutput(int deriv = 0);
        void randomizeWeights();
    };
}
#endif /* NERUON_H */
