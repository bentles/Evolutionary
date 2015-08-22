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
using std::stod;

namespace nnet
{
    class DataSet {
    private:
        int m_output_column;
        vector<double> m_outputs;
        vector<vector<double> > m_patterns;
    public:
        DataSet(const string &filename, int output_column = -1);
        const vector<double> &DataSet::getPattern(int i);
        int size();
        double getOutput(int i);
        
    }
    
    vector<string> getStrings(const string &filename);
    vector<vector<double> > getDataCsv(const string &filename);
    void printData(const vector<vector<double> > &data);
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);    
    vector<vector<double> > getDataCsv(const ifstream &stream);
}
#endif /* NEURIO_H */
