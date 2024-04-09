#include "Ant.h"
#include <random>
#include <algorithm>

Ant::Ant(const Graph& graph) : graph(graph), visited(graph.size(), false) {}

std::vector<int> Ant::getTour() const {
    return tour;
}

double Ant::tourLength() const {
    double length = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        length += graph.distance(tour[i], tour[i + 1]);
    }
    return length;
}

void Ant::findTour(double alpha, double beta) {
    int n = graph.size();
    tour.clear();
    visited.assign(n, false);

    // Randomly choose a starting node
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n - 1);
    int start = dist(gen);
    tour.push_back(start);
    visited[start] = true;

    for (int i = 1; i < n; ++i) {
        double total_prob = 0.0;
        std::vector<double> probs(n, 0.0);

        // Calculate probabilities for unvisited neighboring nodes
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                double pheromone = graph.getPheromone(tour.back(), j);
                double visibility = 1.0 / graph.distance(tour.back(), j);
                probs[j] = pow(pheromone, alpha) * pow(visibility, beta);
                total_prob += probs[j];
            }
        }

        std::uniform_real_distribution<double> dist(0.0, total_prob);
        double threshold = dist(gen);
        double cum_prob = 0.0;
        int next = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                cum_prob += probs[j];
                if (cum_prob >= threshold) {
                    next = j;
                    break;
                }
            }
        }

        if (next == -1) {
            for (int j = 0; j < n; ++j) {
                if (!visited[j]) {
                    next = j;
                    break;
                }
            }
        }

        tour.push_back(next);
        visited[next] = true;
    }
}
