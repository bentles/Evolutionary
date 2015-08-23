#include "functions.h"
#include <math.h>

namespace nnet {
    double Sigmoid::apply(double net, int deriv) {
        if (deriv == 0)
            return 1/(1 + exp(-net*(1))); //1 is lambda I may need to add functionality to control it
        else if (deriv == 1)
        {
            double signet = 1/(1 + exp(-net*(1)));
            return signet * (1 - signet);
        }
        
    }

    double Linear::apply(double net, int deriv) {
        return net;
    }

    double Ramp::apply(double net, int deriv) {
        if (net < -1)
            return 0;
        else if (net > 1)
            return 1;
        else
            return net;
    }

    double Step::apply(double net, int deriv) {
        return net < 0 ? 0 : 1;
    }
}
