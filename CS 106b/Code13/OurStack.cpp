#include "OurStack.h"
#include "error.h"

const int DEFAULT_SIZE = 4;

OurStack::OurStack() {
	logicalLength = 0;
	elems = new int[DEFAULT_SIZE];
	allocatedLength = DEFAULT_SIZE;
}

OurStack::~OurStack() {
	delete[] elems;
}

int OurStack::size() {
	return logicalLength;
}

bool OurStack::isEmpty() {
	return size() == 0;
}

void OurStack::push(int value) {
	if (logicalLength == allocatedLength) {
		error("No space left!");
	}

	elems[logicalLength] = value;
	logicalLength ++;
}

int OurStack::top() {
	if (isEmpty()) {
		error("What is the sound of one hand clapping?  Same thing.");
	}
	
	return elems[logicalLength - 1];
}

int OurStack::pop() {
	int result = top();
	logicalLength --;
	return result;
}


