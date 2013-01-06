/*********************************************************
 * File: OurStack.hh
 *
 * A class representing a stack that holds integers.
 */
#ifndef OurStack_Included
#define OurStack_Included

class OurStack {
public:
	OurStack();
	~OurStack();

	int size();
	bool isEmpty();
	
	void push(int value);
	int top();
	int pop();

private:
	struct Cell {
		int value;
		Cell* next;
	};
	
	Cell* head;
	// int size;
};


#endif
