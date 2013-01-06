/*****************************************************
 * File: StackTimeTest.cpp
 *
 * A program to run stress tests of our stack.
 */
#include <iostream>
#include <ctime>
#include "OurStack.h"
#include "stack.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int MAXIMUM_SIZE = 100000000;

template <typename StackType>
	void runTimeTrial() {

	double startTime = clock();

	StackType stack;
	
	/* Push, then pop, a huge number of elements. */
	for (int elem = 0; elem < MAXIMUM_SIZE; elem++) {
		stack.push(elem);
	}
	for (int elem = 0; elem < MAXIMUM_SIZE; elem++) {
		stack.pop();
	}
		
	double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
	cout << "Time to push/pop " << MAXIMUM_SIZE << " elements: " << elapsed << "s" << endl;
}

int main() {
	runTimeTrial< OurStack > ();
	runTimeTrial< Stack<int> >();
	
	return 0;
}
