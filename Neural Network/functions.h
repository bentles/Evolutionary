#include "func.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace nnet
{
    class Sigmoid : public IFunc {
    public:
        virtual float apply(float net);  
    };

    class Ramp : public IFunc {
    public:
        virtual float apply(float net);  
    };
    
    class Linear : public IFunc {        
    public:
        virtual float apply(float net);
    };
    
    class Step : public IFunc {        
    public:
        virtual float apply(float net);
    };
}

#endif /* FUNCTIONS_H */
