#include<iostream>
#include "TSP.h"
using namespace std;


int main() {
	ifstream file("simple_dataset.txt");// Dataset file
	if (!file.is_open()) {
		cout << "File can't open" << endl;
		return 1;
	}
	TSP tsp1;
	tsp1.importTSPDataSet(file);//Import

//	tsp1.printTSPGraph();//Print

	cout << "So thanh pho: " << tsp1.cities_num << endl;

	int start = 0;

	tsp1.BruteForce(start);


	file.close();
}