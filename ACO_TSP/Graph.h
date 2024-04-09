
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<double>> pheromones;

public:
    Graph(const std::vector<std::vector<int>>& distances);
    int size() const;
    double distance(int from, int to) const;
    double getPheromone(int from, int to) const;
    void updatePheromones(const std::vector<std::vector<double>>& pheromone_delta);
};

#endif
