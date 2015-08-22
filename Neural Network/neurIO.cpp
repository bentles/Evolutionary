#include "neurIO.h"

namespace nnet {
    //output column that is negative means no ouput
    DataSet::DataSet(const string &filename, int output_column)
    {
        vector<string> strings = getStrings(filename);
        assert(strings.size() > 0); //dataset must have entries
        assert(strings[0].size() > 0); //entry must have fields, not gonna validate them all though
        
        //output column is either:
        //negative for no output
        //0 for the first column or (size - 1) for the last column     
        assert(output_column <= 0 || output_column == (strings[0].size - 1));
        
        m_output_column = output_column;
        
        for (int i = 0; i < strings.size(); i++) {
            if (output_column < 0) //no output
                m_patterns.push_back(split(stod(strings[i])));
            else {                
                int pos;
                string rest_text;

                if (output_column == 0) {
                    pos = strings[i].find(",");
                    string rest_text strings[i].substr(pos + 1);
                    m_outputs[i] = stod(strings[i].substr(0, pos));
                }
                else {
                    pos = strings[i].find_last_of(",");
                    string rest_text strings[i].substr(0, pos);
                    m_outputs[i] = stod(strings[i].substr(pos+1));
                }
                
                vector<string> rest = split(rest_text);            
                std::vector<double> doubleVector(stringVector.size());
                //wtf is this syntax
                std::transform(rest.begin(), rest.end(), doubleVector.begin(),
                               [](const std::string& val)
                               {
                                   return std::stod(val);
                               });
            }
        }
    }

    DataSet::size() {
        return m_patterns.size();
    }

    //we can just copy this each time it's no big deal
    double DataSet::getOutput(int i) {
        assert(m_output_column >= 0);
        return m_patterns[i][m_output_column];
    }

    //want access to pattern without copying but don't want them to be able to modify it
    const vector<double> &DataSet::getPattern(int i) {
        return const &m_patterns[i];
            
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
