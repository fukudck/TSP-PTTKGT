#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std::chrono;
using namespace std;

const int POPULATION_SIZE = 100;
const int NUM_GENERATIONS = 100;
const double CROSSOVER_RATE = 0.5;
const double MUTATION_RATE = 0.7;

int numCities = 200;
vector<vector<int>> distances;/* = {
    {0, 29, 82, 46, 68, 52, 72, 42, 51, 55, 29, 74, 23, 72, 46},
    {29, 0, 55, 46, 42, 43, 43, 23, 23, 31, 41, 51, 11, 52, 21},
    {82, 55, 0, 68, 46, 55, 23, 43, 41, 29, 79, 21, 64, 31, 51},
    {46, 46, 68, 0, 82, 15, 72, 31, 62, 42, 21, 51, 51, 43, 64},
    {68, 42, 46, 82, 0, 74, 23, 52, 21, 46, 82, 58, 46, 65, 23},
    {52, 43, 55, 15, 74, 0, 61, 23, 55, 31, 33, 37, 51, 29, 59},
    {72, 43, 23, 72, 23, 61, 0, 42, 23, 31, 77, 37, 51, 46, 33},
    {42, 23, 43, 31, 52, 23, 42, 0, 33, 15, 37, 33, 33, 31, 37},
    {51, 23, 41, 62, 21, 55, 23, 33, 0, 29, 62, 46, 29, 51, 11},
    {55, 31, 29, 42, 46, 31, 31, 15, 29, 0, 51, 21, 41, 23, 37},
    {29, 41, 79, 21, 82, 33, 77, 37, 62, 51, 0, 65, 42, 59, 61},
    {74, 51, 21, 51, 58, 37, 37, 33, 46, 21, 65, 0, 61, 11, 55},
    {23, 11, 64, 51, 46, 51, 51, 33, 29, 41, 42, 61, 0, 62, 23},
    {72, 52, 31, 43, 65, 29, 46, 31, 51, 23, 59, 11, 62, 0, 59},
    {46, 21, 51, 64, 23, 59, 33, 37, 11, 37, 61, 55, 23, 59, 0}
}*///data set p01_d.txt

// Hàm tính tổng chi phí của một đường đi
int calculateCost(const vector<int>& path) {
    int cost = 0;
    for (int i = 0; i < numCities - 1; ++i) {
        cost += distances[path[i]][path[i + 1]];
    }
    cost += distances[path[numCities - 1]][path[0]]; // Chi phí quay về thành phố ban đầu
    return cost;
}

// Hàm tạo một gen ngẫu nhiên (một đường đi ngẫu nhiên)
vector<int> generateRandomPath() {
    vector<int> path(numCities);
    for (int i = 0; i < numCities; ++i) {
        path[i] = i;
    }
    random_shuffle(path.begin(), path.end());
    return path;
}

// Hàm so sánh để sắp xếp các đường đi theo chi phí tăng dần
bool comparePaths(const vector<int>& path1, const vector<int>& path2) {
    return calculateCost(path1) < calculateCost(path2);
}

// Hàm chéo đoạn (crossover) giữa 2 đường đi
vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int startPos = rand() % numCities;
    int endPos = rand() % numCities;
    if (startPos > endPos) {
        swap(startPos, endPos);
    }

    vector<int> child(numCities, -1);
    for (int i = startPos; i <= endPos; ++i) {
        child[i] = parent1[i];
    }

    int currentIndex = 0;
    for (int i = 0; i < numCities; ++i) {
        if (currentIndex == startPos) {
            currentIndex = endPos + 1;
        }
        if (find(child.begin(), child.end(), parent2[i]) == child.end()) {
            child[currentIndex++] = parent2[i];
            currentIndex %= numCities;
        }
    }

    return child;
}

// Hàm đột biến (mutation)
void mutate(vector<int>& path) {
    int pos1 = rand() % numCities;
    int pos2 = rand() % numCities;
    swap(path[pos1], path[pos2]);
}
void import(ifstream & file) {
    string line;
    while (getline(file, line)) {
        vector<int> row;
        istringstream iss(line);
        int number;

        while (iss >> number) {
            row.push_back(number);
        }

        distances.push_back(row);
        numCities += 1;
    }
}
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
    // Khởi tạo quần thể ban đầu
    //ifstream file("input.txt");// Dataset file
    //import(file);


    //file.close();



    int maxDistance = 100; // do dai toi da
    int seed = 10042024;
    vector<std::vector<int>> matrix = generateRandomMatrix(numCities, maxDistance, seed);
    distances = matrix;


    auto start_time = high_resolution_clock::now();

    vector<vector<int>> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population.push_back(generateRandomPath());
    }

    int bestCost = INT16_MAX; 
    vector<int> bestPath(numCities); 
    vector<int> currentBestPath(numCities);

    // Lặp qua các thế hệ
    for (int generation = 0; generation < NUM_GENERATIONS; ++generation) {
        // Sinh ra các đường đi mới từ quá trình chéo đoạn và đột biến
        vector<vector<int>> newPaths;
        for (int i = 0; i < POPULATION_SIZE * CROSSOVER_RATE; ++i) {
            int parent1Index = rand() % POPULATION_SIZE;
            int parent2Index = rand() % POPULATION_SIZE;
            vector<int> child = crossover(population[parent1Index], population[parent2Index]);
            newPaths.push_back(child);
        }

        for (int i = 0; i < POPULATION_SIZE * MUTATION_RATE; ++i) {
            int index = rand() % population.size();
            mutate(population[index]);
            newPaths.push_back(population[index]);
        }

        // Thêm các đường đi mới vào quần thể hiện tại
        population.insert(population.end(), newPaths.begin(), newPaths.end());

        // Sắp xếp quần thể theo chi phí
        sort(population.begin(), population.end(), comparePaths);

        // Lấy đường đi có chi phí thấp nhất trong thế hệ này
        vector<int> currentBestPath = population[0];
        int currentBestCost = calculateCost(currentBestPath);

        // So sánh chi phí của đường đi tốt nhất hiện tại với chi phí của đường đi tốt nhất trong thế hệ
        if (currentBestCost < bestCost) {
            bestPath = currentBestPath;
            bestCost = currentBestCost;
        }

        population.resize(POPULATION_SIZE);

        // Cắt bớt quần thể để duy trì kích thước quần thể không đổi
        while (population.size() > POPULATION_SIZE) {
            population.pop_back();
        }

        // In ra chi phí của đường đi ngắn nhất trong thế hệ hiện tại
        cout << "Generation " << generation + 1 << ", shortest path cost: " << calculateCost(population[0]) << endl;
        cout << "Best path cost so far: " << bestCost << endl;
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);
    float time = (duration.count()) / (1e+9);

    cout << "\nTime : " << std::fixed << std::setprecision(7) << time << " s" << endl;

    // Kết quả là đường đi có chi phí thấp nhất
    cout << "Best path: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
    return 0;
}
