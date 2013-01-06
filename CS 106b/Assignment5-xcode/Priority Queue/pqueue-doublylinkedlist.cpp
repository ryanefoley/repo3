/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
    logicalLength = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return logicalLength;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return logicalLength == 0;
}

//This function is similar to that of the linked list, only that when wiring the new cell in to the list, we have to create pointers in both directions instead of just the one.
void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Cell* newCell = new Cell;
    newCell->value = value;
	newCell->next = NULL;
    newCell->prev = NULL;
    
    if(head == NULL) //if the list is empty, the new cell is the head.
        head = newCell;
    else{
        if(head->value > newCell->value){ //if the new cell's value comes before that of the head, then wiring in the new cell in to the front as the new head.
            head->prev = newCell;
            newCell->next = head;
            head = newCell;
        }else{
            if(head->next == NULL){ //checking whether the cell after head exists. If not wiring new cell in.
                head->next = newCell;
                newCell->prev = head;
            }else{ //given that there are atleast two preexisting cells in the list, we look through the list to find the new cell's appropriate position. 
                Cell* prev = head;
                Cell* cur = head->next;
                for(int i = 1; i < logicalLength; i++){
                    if(cur->value > newCell->value){
                        newCell->next = cur;
                        newCell->prev = cur->prev;
                        cur->prev = newCell;
                        prev->next = newCell;
                        break;
                    } else {
                        if(cur->next == NULL){ 
                            cur->next = newCell;
                            newCell->prev = cur;
                            break;
                        }
                        cur = cur->next; 
                        prev = prev->next;
                    }
                }
            }
        }
    }
    logicalLength++;
}

string DoublyLinkedListPriorityQueue::peek() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
	return head->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    if(isEmpty())
        error("Sorry, the queue is empty.");
    
	string result = head->value; 
    head = head->next;
    logicalLength--;
    
	return result;
}

