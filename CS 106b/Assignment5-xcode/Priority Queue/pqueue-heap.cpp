/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

const int DEFAULT_SPACE = 8;

HeapPriorityQueue::HeapPriorityQueue() {
    allocatedLength = DEFAULT_SPACE; //subtract one here because starting indexing at 1 for using the array.
	elems = new string[DEFAULT_SPACE + 1];
	logicalLength = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] elems;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
    return logicalLength == 0;
}

/* Increases the amount of space we have available in the vector. */
void HeapPriorityQueue::grow() {
	/* Growing by a factor of two gives amortized O(1) push. */
	allocatedLength *= 2;
	string* newElems = new string[allocatedLength+1];
	
	/* Copy over the old elements into the new array. */
	for (int i = 0; i <= size(); i++) {
		newElems[i] = elems[i];
	}
	
	/* Free memory for the old array.  Note that this deletes the
	 * array, not the pointer.
	 */
	delete[] elems;
	
	/* Change which array of elements we are now using. */
	elems = newElems;
}

//This is the bubble up function as described in the hwk. It moves a value at an index to it's appropriate position in the heap.
void HeapPriorityQueue::bubbleUp(int index){
    string temp;
    //Checking the values of those in the positions above the current index.
    while(index > 1){
        if(elems[index/2] > elems[index]){ 
            temp = elems[index/2];
            elems[index/2] = elems[index];
            elems[index] = temp;
        } else break;
        index = index/2;
    }
}

void HeapPriorityQueue::bubbleDown(){
    int index = 1;
    string temp;
    while(2*index <= size()){
        /* check if string at parent node is larger (later in the alphabet) than child
         * but that child is also the smaller of the two - other wise we would have to also 
         * bubble down that child node after swapping. */
        if(elems[index] > elems[2*index] && elems[2*index] < elems[2*index+1]){ 
            temp = elems[index];
            elems[index] = elems[2*index];
            elems[2*index] = temp;
            index = 2*index;
        } else {
            if(2*index+1 <= size() && elems[index] > elems[2*index+1]){
                temp = elems[index];
                elems[index] = elems[2*index+1];
                elems[2*index+1] = temp;
                index = 2*index + 1;
            } else break;
        }
    }
}

void HeapPriorityQueue::enqueue(string value) {
    if(size() == allocatedLength)
        grow();
    elems[size()+1] = value;
    bubbleUp(size()+1);
    logicalLength++;
}

string HeapPriorityQueue::peek() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
	return elems[1];
}

string HeapPriorityQueue::dequeueMin() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
    string value = elems[1];
    elems[1] = elems[size()];
    logicalLength--;
    bubbleDown();
    return value;
}

