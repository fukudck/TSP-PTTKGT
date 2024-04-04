#include "TSP.h"
#include <iostream>
#include <sstream>

TSP::TSP()
{

}

void TSP::importTSPDataSet(ifstream& file)
{
    string line;
    while (getline(file, line)) {
        vector<int> row;
        istringstream iss(line);
        int number;

        while (iss >> number) {
            row.push_back(number);
        }

        graph.push_back(row);
    }
    
}

void TSP::printTSPGraph()
{
    for (const auto& row : graph) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}
