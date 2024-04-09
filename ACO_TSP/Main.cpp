#include "Node.h"
#include "Graph.h"
#include "Ant.h"
#include "ACO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono> 
#include <iomanip>
using namespace std::chrono;


std::vector<std::vector<int>> generateRandomMatrix(int numCities, int maxDistance, int seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, maxDistance);

    std::vector<std::vector<int>> matrix(numCities, std::vector<int>(numCities, 0));

    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            int distance = dist(rng);
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }
    }

    return matrix;
}

int main() {
    MAIN:
    int maxDistance = 100; // do dai toi da
    int seed = 10042024;
    int num1 = 10;
    std::cin >> num1;
    std::vector<std::vector<int>> distances = generateRandomMatrix(num1, maxDistance, seed);;

    Graph graph(distances);

    double alpha = 1.0;
    double beta = 2.0;
    double evaporation_rate = 0.5;
    double pheromone_initial = 1.0;
    double Q = 1.0;
    int ant_count = 10;
    int max_iterations = 100;
    auto start_time = high_resolution_clock::now();

    ACOSolver aco_solver(graph, alpha, beta, evaporation_rate, pheromone_initial, Q, ant_count, max_iterations);
    aco_solver.run();

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);
    float time = (duration.count()) / (1e+9);


    std::vector<int> best_solution = aco_solver.getBestSolution();
    double best_solution_length = aco_solver.getBestSolutionLength();

    std::cout << "Best solution found: ";
    for (int node_id : best_solution) {
        std::cout << node_id << " ";
    }
    std::cout << std::endl;
    std::cout << "Length of the best solution: " << best_solution_length << std::endl;
    std::cout << "Time : " << std::fixed << std::setprecision(7) << time << " s" << std::endl;
    goto MAIN;

    return 0;
}
