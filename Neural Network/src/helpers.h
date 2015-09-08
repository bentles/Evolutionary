#ifndef HELPERS_H
#define HELPERS_H

#include <numeric>
#include <iostream>
#include <vector>

namespace nnet
{
    struct KahanAccumulation
    {
        double sum;
        double correction;
    };

    KahanAccumulation KahanSum(KahanAccumulation accumulation, double value);
}


#endif /* HELPERS_H */
