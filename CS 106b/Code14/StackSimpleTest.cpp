/*****************************************************
 * File: StackSimpleTest.cpp
 *
 * A program to run simple tests on our custom Stack.
 */
#include <iostream>
#include "OurStack.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int NUM_ELEMS = 1000;

int main() {
	OurStack stack;
	
	/* Load the stack with random values. */
	for (int i = 0; i < NUM_ELEMS; i++) {
		int value = randomInteger(0, 1000);
		cout << "Pushing " << value << " onto the stack." << endl;
		stack.push(value);
	}
	
	/* See what those values are. */
	while (!stack.isEmpty()) {
		cout << "Popped " << stack.pop() << " from the stack." << endl;
	}
	
	return 0;
}
