/***********************************************
 * File: HuffmanPQueue.h
 *
 * A priority queue class specialized to store
 * nodes in a Huffman encoding tree.
 */
#ifndef HuffmanPQueue_Included
#define HuffmanPQueue_Included

#include <queue>		// For priority_queue
#include <vector>		// For vector
using namespace std;

struct Node;			// Forward-declaration of the Node type.

class HuffmanPQueue {
public:
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a node into the priority queue. */
	void enqueue(Node* tree);
	
	/* Returns, but does not remove, the least-weight tree in the
	 * priority queue.
	 */
	Node* peek();
	
	/* Returns and removes the least-weight tree in the priority
	 * queue.
	 */
	Node* dequeueMin();

private:
	/* Comparator functor class for comparing nodes. */
	struct NodeComparator {
		bool operator() (Node* lhs, Node* rhs);
	};

	/* Our priority queue is backed by the C++ standard priority_queue
	 * type, which is in turn implemented using a binary heap.
	 */
	priority_queue<Node*, vector<Node*>, NodeComparator> elems;
};

#endif
