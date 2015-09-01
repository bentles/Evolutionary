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
    string indep_t = "../Data/Training5/HourlyInputTraining.csv";
    string dep_t = "../Data/Training5/HourlyOutputTraining.csv";
    DataResultsSet training = DataResultsSet(indep_t , dep_t);
    DataResultsSet training2 = DataResultsSet(indep_t , dep_t);
    
    string indep_v = "../Data/Validation3/HourlyInputValidation.csv";
    string dep_v = "../Data/Validation3/HourlyOutputValidation.csv";
    DataResultsSet validation = DataResultsSet(indep_v , dep_v);

    string indep_test = "../Data/Test1/HourlyInputTest.csv";
    DataSet test = DataSet(indep_test);
    
    Linear lin;
    Sigmoid sig;
    Cosine cos;
    Sine sin;
    
    //half sin and half cos because why not
    vector<Neuron> specialHidden;
    for (int i = 0; i < 4; i++) {
        specialHidden.push_back(Neuron(4, sin));        
    }
    for (int i = 4; i < 8; i++) {
        specialHidden.push_back(Neuron(4, lin));        
    }
    
    StandardFFNN network = StandardFFNN(
        lin, 4,
        sin, 15, //how many of these should I have? we shall experiment
        lin, 24,
        training,
        validation,
        test);
    
    //method chaining <3
    network
        .setLearnRate(0.005)
        .setMomentum(0.7)
        .verbose(true)
        .trainFor(4000)
        .setTrainingSet(training2) //unshuffled copy
        //   .printOutputs()
        ;   //this is so i can comment out the last line lol 
    return 0;
}
