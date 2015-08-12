#ifndef FUNC_H
#define FUNC_H

namespace nnet {
    class Func {
        int const m_diff;
    public:
        virtual double apply(double net, int diff = 0) = 0;
    protected:
        Func(int diff = 0) : m_diff(diff){}
    };
}

#endif /* FUNC_H */
