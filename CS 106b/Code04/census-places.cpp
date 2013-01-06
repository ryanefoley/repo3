/* File: census-places.txt
 *
 * A program to determine which states have the highest number of cities
 * in them.
 */
#include <iostream>
#include <fstream>
#include "map.h"
#include "vector.h"
#include "foreach.h"
using namespace std;

Map<string, int> loadUSCities() {
	Map<string, int> result;
	
	ifstream input("cities.txt");
	
	while (true) {
		string line;
		getline(input, line);
		
		if (input.fail()) break;
		
		string state = line.substr(line.length() - 2);
		result[state]++;
	}
	
	return result;
}

int main() {
	Map<string, int> stateTotals = loadUSCities();
	
	Map<int, Vector<string> > byPopulation;
	
	foreach (string state in stateTotals) {
		byPopulation[stateTotals[state]] += state;
	}
	
	foreach (int population in byPopulation) {
		foreach (string state in byPopulation[population]) {
			cout << state << ": " << population << endl;
		}
	}
}





