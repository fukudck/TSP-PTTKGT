#pragma once
#include <vector>
#include <fstream>
using namespace std;
class TSP
{
public:
	vector<vector<int>> graph;
	TSP();
	void importTSPDataSet(ifstream& file);


	//Test Func
	void printTSPGraph();
};

