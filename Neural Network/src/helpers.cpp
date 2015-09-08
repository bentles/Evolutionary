#include "helpers.h"

namespace nnet
{    
    KahanAccumulation KahanSum(KahanAccumulation accumulation, double value)
    {
        KahanAccumulation result;
        double y = value - accumulation.correction;
        double t = accumulation.sum + y;
        result.correction = (t - accumulation.sum) - y;
        result.sum = t;
        return result;
    }

    /* usage example:
       
    std::vector<double> numbers = {0.01, 0.001, 0.0001, 0.000001, 0.00000000001};
    KahanAccumulation init = {0};
    KahanAccumulation result =
        std::accumulate(numbers.begin(), numbers.end(), init, KahanSum);
    */
    
}
