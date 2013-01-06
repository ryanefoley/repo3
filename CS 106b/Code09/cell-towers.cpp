/* File: cell-towers.cpp
 *
 * Some sample code showing off basic Vector operations.
 */
#include <iostream>
#include <algorithm> // For max
#include "vector.h"
#include "map.h"
using namespace std;

int maximizeCellCoverage(Vector<int>& populations, int index,
                         Map<int, int>& solutions);

int main() {
	Vector<int> populations;
	for (int i = 0; i < 1000; i++)
		populations += i;
	
	Map<int, int> solutions;
	cout << "Maximum amount: "
	     << maximizeCellCoverage(populations, 0, solutions) << endl;
	
	return 0;
}

int maximizeCellCoverage(Vector<int>& populations, int index,
                         Map<int, int>& solutions) {
	/* Base case: If there are no cities, we can't provide any
	 * coverage at all!
	 */
	if (populations.size() == index) {
		return 0;
	}
	/* Base case: If there is just one city, we can provide coverage
	 * to all of its residents.
	 */
	else if (populations.size() - 1 == index) {
		return populations[index];
	}
	/* Base case: If we already know the answer, just return it! */
	else if (solutions.containsKey(index)) {
		return solutions[index];
	}
	/* Recursive step: We either take the first tower and exclude the
	 * second, or we exclude the first tower.
	 */
	else {	
		/* Compute the answer. */
		int result =
		max(maximizeCellCoverage(populations, index + 1, solutions),
			populations[index] + maximizeCellCoverage(populations, index + 2, solutions));
	 
	 	/* Store it for later usage. */
	 	solutions[index] = result;
	 	
	 	return result;
	}
}





