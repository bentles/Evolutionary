#ifndef FUNC_H
#define FUNC_H

namespace nnet {

    class IFunc {
    public:
        virtual float apply(float net) = 0;
    };
}

#endif /* FUNC_H */
