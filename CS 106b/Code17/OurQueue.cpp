#include "OurQueue.h"
#include "error.h"

/* Constructor sets the head/tail pointers to NULL; there is currently
 * nothing in the queue.
 */
OurQueue::OurQueue() {
	head = NULL;
	tail = NULL;
}

/* Destructor cleans up all elements of the queue. */
OurQueue::~OurQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

/* To determine the size of the queue, we count up the number of elements.
 * There are much more efficient ways of doing this; we should be storing
 * a second integer to keep track of how many elements are here.
 */
int OurQueue::size() {
	int result = 0;
	for (Cell* curr = head; curr != NULL; curr = curr->next) {
		result++;
	}
	return result;
}

/* Determines whether the queue is empty. */
bool OurQueue::isEmpty() {
	return head == NULL;
}

/* Enqueues a value at the end of the linked list. */
void OurQueue::enqueue(int value) {
	/* Create a new cell to hold the value.  It goes at the end of the list,
	 * so its next pointer will be NULL.
	 */
	Cell* cell = new Cell;
	cell->value = value;
	cell->next = NULL;
	
	/* If the list is empty, insert it at the front. */
	if (head == NULL) {
		head = cell;
	}
	/* Otherwise, insert it after the last element. */
	else {
		tail->next = cell;
	}

	/* Update the tail pointer to point to the new end of the list; namely
	 * this cell.
	 */	
	tail = cell;		
}

/* The front of the queue is the first linked list cell. */
int OurQueue::front() {
	if (isEmpty()) {
		error("Why did you do that?  That makes bunnies sad.");
	}
	
	return head->value;
}

/* Removes and returns the first element. */
int OurQueue::dequeue() {
	if (isEmpty()) {
		error("Why did you do that?  That makes bunnies sad.");
	}
	
	/* We're ultimately handing back a value from the first cell.
	 * We need to cache this so that we can update the list.
	 */
	Cell* result = head;
	
	/* The head is now the cell right after this one.  If we just
	 * got rid of the last element, then set the tail to NULL as
	 * well.
	 */
	head = head->next;
	if (head == NULL) {
		tail = NULL;
	}
	
	/* Cache the value to return so that we can free the memory for
	 * the linked list cell.
	 */
	int value = result->value;
	delete result;
	
	return value;
}


