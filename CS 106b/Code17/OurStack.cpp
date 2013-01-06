#include "OurStack.h"
#include "error.h"

/* Constructor sets the head to NULL, since there are no elements. */
OurStack::OurStack() {
	head = NULL;
}

/* Destructor frees all elements. */
OurStack::~OurStack() {
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
int OurStack::size() {
	int result = 0;
	for (Cell* curr = head; curr != NULL; curr = curr->next) {
		result++;
	}
	return result;
}

/* The stack is empty if there is no head element. */
bool OurStack::isEmpty() {
	return head == NULL;
}

/* Pushing a value prepends it to the linked list. */
void OurStack::push(int value) {
	Cell* cell = new Cell;
	cell->value = value;
	cell->next = head;
	head = cell;
}

/* The top of the stack is at the front of the list. */
int OurStack::top() {
	if (isEmpty()) {
		error("Why did you do that?  That makes bunnies sad.");
	}
	
	return head->value;
}

/* Popping the stack removes and returns the first linked list cell's
 * value.
 */
int OurStack::pop() {
	if (isEmpty()) {
		error("Why did you do that?  That makes bunnies sad.");
	}
	
	Cell* result = head;
	head = head->next;
	
	
	int value = result->value;
	delete result;
	return value;
}


