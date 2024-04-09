#include<iostream>
#include "TSP.h"
using namespace std;
#include <random>

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
	//ifstream file("p01_d.txt");// Dataset file
	//if (!file.is_open()) {
	//	cout << "File can't open" << endl;
	//	return 1;
	//}
	
//	tsp1.importTSPDataSet(file);//Import


	int start = 0;
	bool loop = true;
	while (loop) {
		int num1 = 0; // so thanh pho
		cout << "Nhap so thanh pho: "; cin >> num1;
		int maxDistance = 100; // do dai toi da
		int seed = 10042024;
		vector<std::vector<int>> matrix = generateRandomMatrix(num1, maxDistance, seed);
		TSP tsp1(matrix);
		tsp1.printTSPGraph();//Print
		cout << "Bruteforce: \n";
		tsp1.BruteForce(start);
		cout << "\n\Greedy: \n";
		tsp1.Greedy(start);

		cout << endl << "Continue ?(1/0) ";
		cin >> loop;
	}

//	tsp1.Greedy(start);


//	file.close();
}