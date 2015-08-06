#include "neurIO.h"

namespace nnet {
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

    vector<string> getData(const string &filename) {
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
    
    vector<vector<double> > getDataCsv(const string &filename) {
        vector<string> strings = getData(filename);

        if (strings.size() == 0)
        {
            vector<vector<double> > dataset;
            return dataset;
        }
        else {
            vector<string> elements = split(strings[0], ',');
            int size = elements.size();
            
            vector<vector<double> > dataset(size);

            for(int i = 0; i < strings.size(); i++) {
                vector<string> elems = split(strings[i], ',');
                for (int j = 0; j < size; j++) {
                    //std::cout << elems[j] << std::endl;
                    dataset[j].push_back(stof(elems[j]));                    
                }
            }

            return dataset;                
        }
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
