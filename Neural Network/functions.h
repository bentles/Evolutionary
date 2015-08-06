#include "func.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace nnet
{
    class Sigmoid : public IFunc {
    public:
        virtual double apply(double net);  
    };

    class Ramp : public IFunc {
    public:
        virtual double apply(double net);  
    };
    
    class Linear : public IFunc {        
    public:
        virtual double apply(double net);
    };
    
    class Step : public IFunc {        
    public:
        virtual double apply(double net);
    };
}

#endif /* FUNCTIONS_H */
