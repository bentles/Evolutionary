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

    double Cosine::apply(double net, int deriv) {
        int dmod4 = deriv % 4;
        if (dmod4 == 0)
            return cos(net);
        else if (dmod4 == 1)
            return -sin(net);
        else if (dmod4 == 2)
            return -cos(net);
        else
            return sin(net);
    }

    double Sine::apply(double net, int deriv) {
        int dmod4 = deriv % 4;
        if (dmod4 == 0)
            return sin(net);
        else if (dmod4 == 1)
            return cos(net);
        else if (dmod4 == 2)
            return -sin(net);
        else
            return -cos(net);
    }

    double Linear::apply(double net, int deriv) {
        if (deriv == 0)
            return net;
        else if (deriv == 1)
            return 1;
        else
            return 0;
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
