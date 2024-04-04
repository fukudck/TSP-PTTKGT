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

//	cout << endl << tsp1.cities_num;

	int start = 0;

	cout << "\nMinCost =  " << tsp1.BruteForce(start);


	file.close();
}