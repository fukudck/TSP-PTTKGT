#include "ACO.h"
#include <iostream>
#include <limits>
#include <cmath>



ACOSolver::ACOSolver(const Graph& graph, double alpha, double beta, double evaporation_rate, double pheromone_initial,
                     double Q, int ant_count, int max_iterations)
    : graph(graph), alpha(alpha), beta(beta), evaporation_rate(evaporation_rate), pheromone_initial(pheromone_initial),
      Q(Q), ant_count(ant_count), max_iterations(max_iterations) {}

void ACOSolver::initializePheromones() {
    int n = graph.size();
    pheromones.resize(n, std::vector<double>(n, pheromone_initial));
}

void ACOSolver::calculateProbabilities(double alpha, double beta) {
    int n = graph.size();
    std::vector<std::vector<double>> probabilities(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double pheromone_ij = pheromones[i][j];
                double visibility_ij = 1.0 / graph.distance(i, j);
                probabilities[i][j] = pow(pheromone_ij, alpha) * pow(visibility_ij, beta);
            }
        }
    }
}

void ACOSolver::updatePheromones() {
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pheromones[i][j] *= (1 - evaporation_rate);
        }
    }

    for (const Ant& ant : ants) {
        const std::vector<int>& tour = ant.getTour();
        double tour_length = ant.tourLength();
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            int from = tour[i];
            int to = tour[i + 1];
            pheromones[from][to] += (Q / tour_length);
            pheromones[to][from] = pheromones[from][to]; // Reverse to keep pheromone matrix symmetric
        }
    }
}

void ACOSolver::run() {
    initializePheromones();

    for (int iter = 0; iter < max_iterations; ++iter) {
        ants.clear();
        for (int i = 0; i < ant_count; ++i) {
            ants.emplace_back(graph);
        }
        
        for (Ant& ant : ants) {
            ant.findTour(alpha, beta);
        }

        updatePheromones();
    }

    double min_length = std::numeric_limits<double>::max();
    for (const Ant& ant : ants) {
        double length = ant.tourLength();
        if (length < min_length) {
            min_length = length;
            best_solution = ant.getTour();
            best_solution_length = length;
        }
    }
}

std::vector<int> ACOSolver::getBestSolution() const {
    return best_solution;
}

double ACOSolver::getBestSolutionLength() const {
    return best_solution_length;
}
