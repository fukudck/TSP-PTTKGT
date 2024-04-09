#ifndef ACO_H
#define ACO_H

#include <vector>
#include "Graph.h"
#include "Ant.h"

class ACOSolver {
private:
    Graph graph;
    double alpha;
    double beta;
    double evaporation_rate;
    double pheromone_initial;
    double Q;
    std::vector<Ant> ants;
    int ant_count;
    int max_iterations;

    std::vector<std::vector<double>> pheromones;
    std::vector<int> best_solution;
    double best_solution_length;

public:
    ACOSolver(const Graph& graph, double alpha, double beta, double evaporation_rate, double pheromone_initial,
              double Q, int ant_count, int max_iterations);
    void initializePheromones();
    void calculateProbabilities(double alpha, double beta); // Không cần tham số ở đây
    void updatePheromones();
    void run();
    std::vector<int> getBestSolution() const;
    double getBestSolutionLength() const;
};

#endif
