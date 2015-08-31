#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <stdlib.h>
#include "helpers.h"
#include "func.h"

using std::vector;

namespace nnet
{
    class Neuron {
    private:
        vector<KahanAccumulation> m_weights;
        vector<double> m_inputs;
        vector<double> m_prev_delta_w;
        int m_size;

        //cache net value, change valid to false invalidate cached value
        double m_net;
        bool m_valid;
        
        Func& m_function;
        double getNet();
    public:
        double getInput(int index);
        double getWeight(int index);
        Neuron(int s, Func& function);        
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
