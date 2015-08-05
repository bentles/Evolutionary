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
    vector<string> getData(const string &filename);
    vector<vector<float> > getDataCsv(const string &filename);
    void printData(const vector<vector<float> > &data);
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);    
    vector<vector<float> > getDataCsv(const ifstream &stream);
}
#endif /* NEURIO_H */
