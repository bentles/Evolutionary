#include "neurIO.h"

namespace nnet {
    //output column that is negative means no ouput
    DataSet::DataSet(const string &independent)
    {
        vector<string> strings = getStrings(independent);
        
        assert(strings.size() > 0); //dataset must have entries
        assert(strings[0].size() > 0); //entry must have fields, not gonna validate them all though
        
        for (int i = 0; i < strings.size(); i++)
        {
            vector<string> fields = split(strings[i], ',');           
            std::vector<double> doubleVector(fields.size());
            for (int k = 0; k < fields.size(); k++) {
                doubleVector[k] = stod(fields[k]);
            }
            m_patterns.push_back(doubleVector);
        }        
                
    }

    void DataSet::print()
    {
        for (int i = 0; i < m_patterns.size(); i++) {
            int j = 0;
            for (; j < m_patterns[0].size() -1; j++) {
                std::cout << m_patterns[i][j] << ", ";
            }
            std::cout << m_patterns[i][j] << std::endl;
        }

    }

    //good ole fisher yates
    void DataResultsSet::shuffle()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0,1);
        
        for (int i = m_patterns.size() - 1; i > 0; i--) {
            int pos = (int)floor(dist(mt) * (i + 1));
            
            //patterns
            vector<double> temp = m_patterns[i];
            m_patterns[i] = m_patterns[pos];
            m_patterns[pos] = temp;
            
            //results
            vector<double> temp2 = m_dependents[i];
            m_dependents[i] = m_dependents[pos];
            m_dependents[pos] = temp2;
        }

    }

    int DataSet::size() {
        return m_patterns.size(); 
    }

    int DataSet::fieldSize() {
        return m_patterns[0].size();
    }
    
    //we can just copy this each time it's no big deal
    vector<double> DataResultsSet::getOutputs(int i) {
        return m_dependents[i];
    }

    //want access to pattern without copying but don't want them to be able to modify it
    const vector<double> &DataSet::getPattern(int i) {
        return m_patterns[i];            
    }


    DataResultsSet::DataResultsSet(const string &independent,
                                   const string &dependent) : DataSet(independent)
    {
        vector<string> strings = getStrings(dependent);
        
        assert(strings.size() > 0); //dataset must have entries
        assert(strings[0].size() > 0); //entry must have fields, not gonna validate them all though
        
        for (int i = 0; i < strings.size(); i++)
        {
            vector<string> fields = split(strings[i], ',');           
            std::vector<double> doubleVector(fields.size());
            for (int k = 0; k < fields.size(); k++) {
                doubleVector[k] = stod(fields[k]);
            }
            m_dependents.push_back(doubleVector);
        }   
    }
    
    vector<string> &split(const string &s, char delim, vector<string> &elems) {
        std::stringstream ss(s);
        string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    vector<string> split(const string &s, char delim) {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }

    vector<string> getStrings(const string &filename) {
        string line;
        ifstream stream = ifstream(filename);
        vector<string> strings;
        if (stream.is_open())
        {
            while ( std::getline(stream, line))
            {
                strings.push_back(line);
            }
            stream.close();
        }
        else std::cout << "Unable to open file";

        return strings;
    }

    void printData(const vector<vector<double> > &data)
    {
        for (int i = 0; i < data[0].size(); i++)
        {
            for (int j = 0; j < data.size(); j++)
                std::cout << (data[j])[i] << ',';
            std::cout << std::endl;
        }
    }
}
