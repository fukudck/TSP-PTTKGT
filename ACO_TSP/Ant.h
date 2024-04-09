#ifndef ANT_H
#define ANT_H

#include <vector>
#include "Graph.h"

class Ant {
private:
    std::vector<int> tour;
    std::vector<bool> visited;
    const Graph& graph;

public:
    Ant(const Graph& graph);
    std::vector<int> getTour() const;
    double tourLength() const;
    void findTour(double alpha, double beta);
};

#endif
