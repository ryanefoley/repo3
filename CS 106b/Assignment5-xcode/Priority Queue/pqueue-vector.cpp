/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

const int DEFAULT_SPACE = 8;

VectorPriorityQueue::VectorPriorityQueue(int startSize) {
    // allocatedLength
	allocatedLength = startSize;
	if (allocatedLength < DEFAULT_SPACE)
		allocatedLength = DEFAULT_SPACE;
    
	// elems
	elems = new string[allocatedLength];
	
	// logicalLength
	logicalLength = startSize;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	delete[] elems;
}

int VectorPriorityQueue::size() {
	return logicalLength;
}

bool VectorPriorityQueue::isEmpty() {
	return size() == 0;
}


/* This grow function was just taken as is from the lecture notes:
 * Increases the amount of space we have available in the vector. */
void VectorPriorityQueue::grow() {
	/* Growing by a factor of two gives amortized O(1) push. */
	allocatedLength *= 2;
	string* newElems = new string[allocatedLength];
	
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

void VectorPriorityQueue::enqueue(string value) {
	if(allocatedLength == size()) //if our array needs more space, we call the grow function.
        grow();
    
    elems[size()] = value; //put value at end of array
    logicalLength++;
    
}

string VectorPriorityQueue::peek() {
    if(size() == 0) //can't peek if vector empty
        error("The queue is empty.");
    
    string str = elems[0];
    
    for(int i = 1; i < size(); i++) //finding first (alphabetically) string
        if(str > elems[i]){ //if the string in the array comes before str, then replace str
            str = elems[i];
        }
    
    return str;
}

string VectorPriorityQueue::dequeueMin() {
	if(size() == 0) //can't dequeue if vector empty
        error("The queue is empty.");
    
    string str = elems[0];
    int index = 0;
    //finding the first string (alphabetically) and storing its value and index in the array
    for(int i = 1; i < size(); i++){ 
        if(str > elems[i]){
            str = elems[i];
            index = i;
        }
    }
    //moving all elements after dequeue index forward by one position
    for(int j = index; j <size()-1; j++)
        elems[j] = elems[j+1];
            
    logicalLength--;
    
	return str;
}

