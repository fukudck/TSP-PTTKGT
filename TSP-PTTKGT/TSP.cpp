#include "TSP.h"
#include <iostream>
#include <sstream>
#include <chrono> 
#include <iomanip>
using namespace std::chrono;

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

void TSP::BruteForce(int start)
{
    //Pre-Process
    vector<int> path; path.push_back(start);
    int minCost = INT_MAX;
    vector<vector<int>> allPaths;
    vector<int> pathCosts;


    auto start_time = high_resolution_clock::now();
    BruteForceProcess(path, start, 0, minCost, allPaths, pathCosts);
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);
    float time = (duration.count()) / (1e+9);

    int sumOfMinPath = 0;
    if (!pathCosts.empty()) {
        sumOfMinPath = *min_element(pathCosts.begin(), pathCosts.end());
    }

    cout << "Cac nghiem va tong tung nghiem:\n";
    for (int i = 0; i < allPaths.size(); i++) {

        if (pathCosts[i] == sumOfMinPath) { //Chi in nghiem, chinh thanh true de liet ke danh sach path co the
            cout << "Nghiem " << i + 1 << ": ";
            for (int j : allPaths[i]) {
                cout << j << " ";
            }
            cout << start;
            cout << " - Tong: " << pathCosts[i] << endl;
        }
    }
    
    cout << "Tong chi phi nho nhat la: " << sumOfMinPath << endl;
    
    cout << "Time : " << std::fixed << std::setprecision(7) << time << " s" << endl;
}

void TSP::BruteForceProcess(vector<int>& path, int start, int cost, int& minCost, vector<vector<int>>& allPaths, vector<int>& pathCosts)
{
    
    if (path.size() == cities_num) {
        cost += graph[path.back()][start];
        minCost = min(minCost, cost);
        allPaths.push_back(path);
        pathCosts.push_back(cost);
        return;
    }

    for (int i = 0; i < cities_num; i++) {
        if (find(path.begin(), path.end(), i) == path.end()) {
            path.push_back(i);
            cost += graph[path[path.size() - 2]][i];

            BruteForceProcess(path, start, cost, minCost, allPaths, pathCosts);

            cost -= graph[path[path.size() - 2]][i];
            path.pop_back();
        }
    }
}

void TSP::Greedy(int start)
{
    //Pre-Process
    vector<int> visited;
    visited.resize(cities_num);
    int cost = 0;
    cout << "Con duong di ngan nhat la: ";

    auto start_time = high_resolution_clock::now();

    GreedyProcess(start, visited, cost);

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);
    float time = (duration.count()) / (1e+9);
    
    cout << "\nChi phi thap nhat la: "; cout << cost << endl;
    cout << "Time : " << std::fixed << std::setprecision(7) << time << " s" << endl;

}

void TSP::GreedyProcess(int start, vector<int>& visited, int& cost)
{
    /*
    * Visited: danh dau dinh da vieng tham
    * 1 = true, 0 = false
    */
    int u = INT_MAX;
    int path = INT_MAX;

    visited[start] = 1;

    //In ra duong di
    cout << start + 1 << " ";

    //kiem tra chi phi thap nhat, bien k duoc xem la thanh pho tiep theo
    for (int k = 0; k < cities_num; k++) {
        if ((graph[start][k] != 0) && (visited[k] == 0)) {
            if (graph[start][k] < path) {
                path = graph[start][k];
            }
            u = k; // u la thanh pho co khoang cach gan nhat
        }
    }
    if (path != INT_MAX) {
        cost = cost + path;
    }
    if (u == INT_MAX) {
        u = 0;
        cout << u + 1;
        cost = cost + graph[start][u];
        return;
    }
    GreedyProcess(u, visited, cost);

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
