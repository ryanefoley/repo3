/*******************************************
 * File: linked-lists.cpp
 *
 * A program that shows off a simple use of
 * linked lists.
 */

#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

/* Type: Cell
 * A cell in a linked list.
 */
struct Cell {
	string value;
	Cell* next;
};

/* Reads a list of names and returns a linked list containing them. */
Cell* readList();

/* Recursive function to print out a linked list. */
void recursivePrint(Cell* list) {
	/* Base case: If there are no cells left, we're done. */
	if (list == NULL) return;
	
	/* Recursive step: Print the first cell, followed by the rest of the list. */
	cout << list->value << endl;
	recursivePrint(list->next);
	
}

int main() {
	Cell* list = readList();
	
	/* Print out the list recursively. */
	recursivePrint(list);
	
	/* Print out the list iteratvely. */
	for (Cell* ptr = list; ptr != NULL; ptr = ptr->next) {
		cout << ptr->value << endl;
	}
	return 0;
}

Cell* readList() {
	Cell* result = NULL;
	
	while (true) {
		// Read a value from the user
		string value = getLine("Enter value: ");
			
		// If we're done, hand back what we have so far.
		if (value == "") return result;
		
		// Otherwise, build a new linked list cell and prepend it to the list.
		Cell* newCell = new Cell;
		newCell->value = value;
		newCell->next = result;
		result = newCell;
	}
}




