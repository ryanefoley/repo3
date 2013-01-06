/***********************************************
 * File: HuffmanPQueue.cpp
 *
 * Implementation of the HuffmanPQueue class.
 */
#include "HuffmanPQueue.h"
#include "HuffmanTypes.h"
#include "error.h"

/*
 * Member function HuffmanPqueue::size
 * ----------------------------------------
 * Calls down to the underlying priority queue to determine
 * the size of the priority queue.
 */
int HuffmanPQueue::size() {
	return elems.size();
}

/*
 * Member function HuffmanPqueue::isEmpty
 * ----------------------------------------
 * Calls down to the underlying priority queue to determine
 * whether the priority queue is empty.
 */
bool HuffmanPQueue::isEmpty() {
	return elems.empty();
}

/*
 * Member function HuffmanPqueue::enqueue
 * ----------------------------------------
 * Enqueues the specified element into the underlying priority
 * queue.
 */
void HuffmanPQueue::enqueue(Node* tree) {
	elems.push(tree);
}

/*
 * Member function HuffmanPqueue::peek
 * ----------------------------------------
 * Peeks at the front of the priority queue.
 */
Node* HuffmanPQueue::peek() {
	if (isEmpty()) error("Cannot peek into an empty priority queue.");
	return elems.top();
}

/*
 * Member function HuffmanPqueue::dequeueMin
 * ----------------------------------------
 * Dequeues the first element of the priority queue.
 */
Node* HuffmanPQueue::dequeueMin() {
	if (isEmpty()) error("Cannot dequeueMin from an empty priority queue.");
	Node* result = elems.top();
	elems.pop();
	
	return result;
}

/*
 * Member function HuffmanPqueue::NodeComparator::operator()
 * ----------------------------------------
 * A comparison function that ranks two nodes.	The weights are compared
 * first to determine whether one node is clearly heavier than the other.
 * If not, the characters are compared.
 */
bool HuffmanPQueue::NodeComparator::operator() (Node* lhs, Node* rhs) {
	if (lhs->weight != rhs->weight) return lhs->weight > rhs->weight;
	return lhs->character > rhs->character;
}

