#include <iostream>
#include "neuron.h"
#include "functions.h"
#include "neurIO.h"
#include "helpers.h"
#include "neuralnetworks.h"
#include <math.h>

int main(int argc, char *argv[])
{
    
    using namespace nnet;


    //get data into useful format
    string indep_t = "../Data/Training1/HourlyInputTraining.csv";
    string dep_t = "../Data/Training1/HourlyOutputTraining.csv";
    DataResultsSet training = DataResultsSet(indep_t , dep_t);
    
    string indep_v = "../Data/Validation1/HourlyInputValidation.csv";
    string dep_v = "../Data/Validation1/HourlyOutputValidation.csv";
    DataResultsSet validation = DataResultsSet(indep_v , dep_v);
    
    Linear lin;
    Sigmoid sig;
    Cosine cos;
    
    StandardFFNN network = StandardFFNN(
        lin, 5,
        cos, 5, //how many of these should I have? we shall experiment
        lin, 1,
        training,
        validation );

    //method chaining <3
    network
        .setLearnRate(0.01)
        .setMomentum(0.9)
        .trainFor(1000);    
    return 0;
}
