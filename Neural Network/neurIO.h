#ifndef NEURIO_H
#define NEURIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <random>
#include <math.h>

using std::string;
using std::vector;
using std::ifstream;
using std::stod;

namespace nnet
{
    class DataSet {
    protected:
        vector<vector<double> > m_patterns;
    public:
        DataSet(const string &indepenent);
        const vector<double> &getPattern(int i);
        int size();
        int fieldSize();
        void print();
    };

    class DataResultsSet : public DataSet {
    private:
        vector<vector<double> > m_dependents;
    public:
        DataResultsSet(const string &independent, const string &dependent);
        vector<double> getOutputs(int i);
        void shuffle();
    };
    
    vector<string> getStrings(const string &filename);
    vector<vector<double> > getDataCsv(const string &filename);
    void printData(const vector<vector<double> > &data);
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);    
    vector<vector<double> > getDataCsv(const ifstream &stream);
}
#endif /* NEURIO_H */
