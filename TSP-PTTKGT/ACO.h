#pragma once
#include "TSP.h"
using namespace std;
class ACOGraph : public TSP
{
public:
	vector<std::vector<double>> distances;
	vector<std::vector<double>> pheromones;

	ACOGraph();
	void importTSPDataSet(ifstream& file);
};
class Ant {
	vector<int> tour;
	vector<bool> visited;
	const ACOGraph& graph;

	Ant(const ACOGraph& graph);
	vector<int> getTour() const;
	double tourLength() const;
	void findTour(double alpha, double beta);
};
class ACOSolver {
public:
	


};


