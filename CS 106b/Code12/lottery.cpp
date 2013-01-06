/* File: lottery.cpp
 *
 * A program that uses the RandomBag to implement a lottery.
 */
#include <iostream>
#include "RandomBag.h"
using namespace std;

/* Constants defining the smallest and largest numbers in the
 * lottery, along with how many values should be chosen.
 */
const int LOWEST_NUMBER = 1;
const int HIGHEST_NUMBER = 50;
const int NUM_VALUES = 5;

int main() {
	/* Fill a random bag with numbers. */
	RandomBag numbers;
	for (int i = LOWEST_NUMBER; i <= HIGHEST_NUMBER; i++) {
		numbers.add(i);
	}
	
	/* Choose some random values. */
	for (int i = 0; i < NUM_VALUES; i++) {
		cout << numbers.removeRandom() << endl;	
	}
	
	return 0;
}
