#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"
#include "helpers.h"
#include <math.h>

int main(int argc, char *argv[])
{
    
    using namespace nnet;
    string indep = "../Data/HourlyInput.csv";
    string dep = "../Data/HourlyOutput.csv";
    DataResultsSet drs = DataResultsSet(indep , dep);

    
    return 0;
}
