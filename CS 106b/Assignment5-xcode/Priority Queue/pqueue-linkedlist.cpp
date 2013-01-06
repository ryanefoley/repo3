/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"


/* Constructor sets the head/tail pointers to NULL; there is currently
 * nothing in the queue.
 */
LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
    logicalLength = 0;
}

/* Destructor cleans up all elements of the queue. */
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int LinkedListPriorityQueue::size() {
	return logicalLength;
}

bool LinkedListPriorityQueue::isEmpty(){ 
    return logicalLength == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	/* Create a new cell to hold the value. */
    Cell* newCell = new Cell;
	newCell->value = value;
	newCell->next = NULL;
    
    /* If the list is empty, insert it at the front. */
    if(head == NULL)
		head = newCell;
    
    //Otherwise, insert the new cell into the appropriate position alphabetically.
    else{
        //If the new cell's value comes before the head's value then that cell is at the beginning of the list.
        if(head->value > newCell->value){
            newCell->next = head;
            head = newCell;
        }else if(head->next == NULL) //If no cell exists after the head, then attach new cell.
            head->next = newCell;
        else{
            Cell* prev = head;
            Cell* cur = head->next;
            for(int i = 1; i < logicalLength; i++){ //look through list and look for new cells appropriate position. When found, wiring in new cell into the list.
                if(cur->value > newCell->value){
                    newCell->next = cur;
                    prev->next = newCell;
                    break;
                } else {
                    if(cur->next == NULL){ 
                        cur->next = newCell;
                        break;
                    }
                    cur = cur->next; 
                    prev = prev->next;
                }
            }
        }
    }
    logicalLength++;
}

//Simply showing the value of the first cell in the list.
string LinkedListPriorityQueue::peek() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
	return head->value;
}

//To dequeue min, just removing the head and making the next cell the new head.
string LinkedListPriorityQueue::dequeueMin() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
    
	string result = head->value;
    head = head->next;
    
    logicalLength--;
    
	return result;
}

