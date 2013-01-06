/*********************************************************
 * File: OurQueue.hh
 *
 * A class representing a queue that holds integers.
 */
#ifndef OurQueue_Included
#define OurQueue_Included

class OurQueue {
public:
	OurQueue();
	~OurQueue();

	int size();
	bool isEmpty();
	
	void enqueue(int value);
	int front();
	int dequeue();

private:
	struct Cell {
		int value;
		Cell* next;
	};
	
	Cell* head;
	Cell* tail;
};


#endif
