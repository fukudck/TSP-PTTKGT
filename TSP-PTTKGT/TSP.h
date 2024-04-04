#pragma once
#include <vector>
#include <fstream>
using namespace std;
class TSP
{
public:
	vector<vector<int>> graph;
	int cities_num = 0;

	TSP();

	void importTSPDataSet(ifstream& file);

	void BruteForce(int start);//Not complete
	void BruteForceProcess(vector<int>& path, int start, int cost, int& minCost, vector<vector<int>>& allPaths, vector<int>& pathCosts); //Not complete

	void Greedy(int start);
	

	//Test Func
	void printTSPGraph();
};

