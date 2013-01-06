/*****************************************************
 * File: StackTimeTest.cpp
 *
 * A program to run stress tests of our stack.
 */
#include <iostream>
#include <ctime>       // For clock, CLOCKS_PER_SEC
#include "OurStack.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int MINIMUM_SIZE = 1000000;
const int MAXIMUM_SIZE = 10000000;
const int STEP_SIZE = 1000000;

int main() {
	for (int i = MINIMUM_SIZE; i <= MAXIMUM_SIZE; i += STEP_SIZE) {
		/* Start the timer. */
		double startTime = clock();
	
		/* Push, then pop, an absurd number of elements. */
		OurStack stack;
		for (int elem = 0; elem < i; elem++) {
			stack.push(elem);
		}
		
		for (int elem = 0; elem < i; elem++) {
			stack.pop();
		}
		
		/* Stop the timer and reports the elapsed time. */
		double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
		cout << "Time for " << i << ": " << elapsed << endl;
	}
	
	return 0;
}
