#include "OurVector.h"
#include "error.h"

const int DEFAULT_SPACE = 8;

OurVector::OurVector(int startSize) {
	// allocatedLength
	allocatedLength = startSize;
	if (allocatedLength < DEFAULT_SPACE)
		allocatedLength = DEFAULT_SPACE;

	// elems
	elems = new int[allocatedLength];
	
	// logicalLength
	logicalLength = startSize;
}

OurVector::~OurVector() {
	delete[] elems;
}

int OurVector::size() {
	return logicalLength;
}

bool OurVector::isEmpty() {
	return size() == 0;
}

void OurVector::insertAt(int value, int index) {
	if (index < 0 || index > size()) {
		error("That index is not okay. :-(");
	}

	if (size() == allocatedLength) {
		grow();
	}
	
	// Add the value
	for (int i = size(); i > index; i--) {
		elems[i] = elems[i - 1];
	}
	
	elems[index] = value;
	logicalLength ++;
}

void OurVector::removeAt(int index) {
	if (index < 0 || index >= size()) {
		error("That index is not okay. :-(");
	}
	
	for (int i = index; i < size() - 1; i++) {
		elems[i] = elems[i + 1];
	}
	
	logicalLength--;
}

void OurVector::append(int value) {
	insertAt(value, size());
}



/* Increases the amount of space we have available in the stack. */
void OurVector::grow() {
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

int OurVector::getAt(int index) {
	if (index < 0 || index >= size()) {
		error("That index is not okay. :-(");
	}

	return elems[index];
}

/* Free function to search the vector for a value. */
bool contains(OurVector& v, int value) {
	for (int i = 0; i < v.size(); i++) {
		if (v.getAt(i) == value) return true;
	}
	
	return false;
}


