#include "Graph.h"
#include <cmath>


Graph::Graph(const std::vector<std::vector<int>>& distances) : distances(distances) {
    int n = distances.size();
    pheromones.resize(n, std::vector<double>(n, 1.0)); // Khởi tạo mùi feromon thành 1.0
}

int Graph::size() const {
    return distances.size();
}

double Graph::distance(int from, int to) const {
    return distances[from][to];
}

double Graph::getPheromone(int from, int to) const {
    return pheromones[from][to];
}

void Graph::updatePheromones(const std::vector<std::vector<double>>& pheromone_delta) {
    // Cập nhật mức độ mùi feromon dựa trên các giá trị delta
    int n = distances.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pheromones[i][j] += pheromone_delta[i][j];
        }
    }
}
