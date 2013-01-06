/* File: cell-towers.cpp
 *
 * Some sample code showing off basic Vector operations.
 */
#include <iostream>
#include <algorithm> // For max
#include "vector.h"
using namespace std;

int maximizeCellCoverage(Vector<int>& populations);

int main() {
	Vector<int> populations;
	populations += 14, 22, 13, 29, 30, 29, 9;
	
	cout << "Maximum amount: " << maximizeCellCoverage(populations) << endl;
	
	return 0;
}

int maximizeCellCoverage(Vector<int>& populations) {
	if (populations.size() == 0) {
		return 0;
	} else if (populations.size() == 1) {
		return populations[0];
	} else {
		Vector<int> allButFirst = populations;
		allButFirst.removeAt(0);
		
		Vector<int> allButFirstTwo = allButFirst;
		allButFirstTwo.removeAt(0);
	
		return max(maximizeCellCoverage(allButFirst),
		           populations[0] + maximizeCellCoverage(allButFirstTwo));
	}
}





