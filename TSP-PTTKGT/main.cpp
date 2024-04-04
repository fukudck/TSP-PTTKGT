#include<iostream>
#include "TSP.h"
using namespace std;


int main() {
	ifstream file("fri26_d.txt");// Dataset file
	if (!file.is_open()) {
		cout << "File can't open" << endl;
		return 1;
	}
	TSP tsp1;
	tsp1.importTSPDataSet(file);//Import

	tsp1.printTSPGraph();//Print


	file.close();
}