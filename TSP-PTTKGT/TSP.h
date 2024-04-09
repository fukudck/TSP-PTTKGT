#pragma once
#include <vector>
#include <fstream>
using namespace std;
class TSP
{
public:
	vector<vector<int>> graph;
	int cities_num = 0;

	TSP(vector<vector<int>>& _graph);

	void importTSPDataSet(ifstream& file);

	void BruteForce(int start);
	void BruteForceProcess(vector<int>& path, int start, int cost, int& minCost, vector<vector<int>>& allPaths, vector<int>& pathCosts);

	void Greedy(int start);
	void GreedyProcess(int start, vector<int>& visited, int& cost);
	

	//Test Func
	void printTSPGraph();
};

