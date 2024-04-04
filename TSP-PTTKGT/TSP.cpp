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
        cities_num += 1;
    }
    
}

int TSP::BruteForce(int start)
{
    //Pre-Process
    vector<int> path; path.push_back(start);

    int minCost = INT_MAX;
    int result = BruteForceProcess(path, start, 0, minCost);
    vector<int> solution_list;
    //cout << "Path: ";
    //for (auto i : path) {
    //    cout << i << " ";
    //}
    return result;
}

int TSP::BruteForceProcess(vector<int>& path, int start, int cost, int& minCost)
{
    if (path.size() == cities_num) {
        cost += graph[path.back()][start];
        minCost = min(minCost, cost);
        return minCost;
    }

    for (int i = 0; i < cities_num; i++) {
        if (find(path.begin(), path.end(), i) == path.end()) {
            path.push_back(i);
            for (auto i : path) {
                cout << i << " ";
            }
            cout << endl;
            cost += graph[path[path.size() - 2]][i];

            BruteForceProcess( path, start, cost, minCost);

            cost -= graph[path[path.size() - 2]][i];
            path.pop_back();
        }
    }

    return minCost;

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
