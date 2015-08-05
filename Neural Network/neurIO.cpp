#include "neurIO.h"

namespace nnet {
    
    vector<string> getData(const ifstream &stream) {
        string line;
        vector<string> strings;
        if (stream.is_open())
        {
            while ( getline (stream,line) )
            {
                strings.push_back(line);
            }
            stream.close();
        }
        else cout << "Unable to open file";

        return strings;
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
    
    vector<vector<float> > getDataCsv(const ifstream &stream) {
        vector<string> strings = getData(&stream);

        if (strings.size() == 0)
            return vector<vector<float> > dataset;
        else {
            vector<string> elements = split(strings[0], ',');
            int size = elements.size();
            
            vector<vector<float> > dataset(size);

            for(int i = 0; i < strings.size(); i++) {
                vector<string> elems = split(strings[i], ',');
                for (int j = 0; j < size; j++) {
                    dataset[i].push_back(stof(elems[j]));                    
                }
            }

            return dataset;                
        }
    }
}
