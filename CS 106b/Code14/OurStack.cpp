/*********************************************
 * File: OurStack.cpp
 *
 * Implementation of our Stack class.
 */

#include "OurStack.h"
#include "error.h"

/* The default array size. */
const int DEFAULT_SIZE = 4;

/* Constructor sets up the initial array and records that there
 * are no elements in the stack.
 */
OurStack::OurStack() {
	logicalLength = 0;
	elems = new int[DEFAULT_SIZE];
	allocatedLength = DEFAULT_SIZE;
}

/* Destructor frees the element array. */
OurStack::~OurStack() {
	delete[] elems;
}

/* Returns how many elements are in the stack. */
int OurStack::size() {
	return logicalLength;
}

/* Determines whether the stack is empty. */
bool OurStack::isEmpty() {
	return size() == 0;
}

/* Increases the amount of space we have available in the stack. */
void OurStack::grow() {
	/* Growing by a factor of two gives amortized O(1) push. */
	allocatedLength *= 2;
	int* newElems = new int[allocatedLength];
	
	/* Copy over the old elements into the new array. */
	for (int i = 0; i < size(); i++) {
		newElems[i] = elems[i];
	}
	
	/* Free memory for the old array.  Note that this deletes the
	 * array, not the pointer.
	 */
	delete[] elems;
	
	/* Change which array of elements we are now using. */
	elems = newElems;
}

/* Adds an element to the stack. */
void OurStack::push(int value) {
	/* If we're out of space, make more room. */
	if (size() == allocatedLength) {
		grow();
	}

	/* Write the element to the next location and increase our logical size. */
	elems[size()] = value;
	logicalLength ++;
}

/* Looks at the top of the stack. */
int OurStack::top() {
	if (isEmpty()) {
		error("What is the sound of one hand clapping?  Same thing.");
	}
	
	return elems[size() - 1];
}

/* Pops the stack. */
int OurStack::pop() {
	int result = top();
	logicalLength --;
	return result;
}


