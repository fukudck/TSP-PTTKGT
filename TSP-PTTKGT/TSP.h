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

	int BruteForce(int start);//Not complete
	int BruteForceProcess(vector<int>& path, int start, int cost, int& minCost); //Not complete

	//Test Func
	void printTSPGraph();
};

