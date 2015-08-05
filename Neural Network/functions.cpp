#include "functions.h"
#include <math.h>

namespace nnet {
    float Sigmoid::apply(float net) {
        return 1/(1 + exp(-net*(1))); //1 is lambda I may need to add functionality to control it
    }
    
    float Linear::apply(float net) {
        return net;
    }

    float Ramp::apply(float net) {
        if (net < -1)
            return 0;
        else if (net > 1)
            return 1;
        else
            return net;
    }
    
    float Step::apply(float net) {
        return net < 0 ? 0 : 1;
    }
}
