#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <climits>
#include "func.h"

namespace nnet
{
    class Sigmoid : public Func {
    public:
        Sigmoid() : Func(INT_MAX){}
        virtual double apply(double net, int deriv = 0);  
    };

    class Cosine : public Func {
    public:
        Cosine() : Func(INT_MAX){}
        virtual double apply(double net, int deriv = 0);  
    };

    class Ramp : public Func {
    public:
        Ramp() : Func(0){}
        virtual double apply(double net, int deriv = 0);  
    };
    
    class Linear : public Func {        
    public:
        Linear() : Func(INT_MAX){}
        virtual double apply(double net, int deriv = 0);
    };
    
    class Step : public Func {        
    public:
        Step() : Func(0){}
        virtual double apply(double net, int deriv = 0);
    };
}

#endif /* FUNCTIONS_H */
