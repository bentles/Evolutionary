#ifndef FUNC_H
#define FUNC_H

namespace nnet {

    class IFunc {
    public:
        virtual double apply(double net) = 0;
    };
}

#endif /* FUNC_H */
