#ifndef NEURIO_H
#define NEURIO_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::vector;
using std::ifstream;
using std::stof;
namespace nnet
{
    vector<string> getData(ifstream const &stream);
    void getDataCsv(vector<vector<float> > const &data);
}
#endif
