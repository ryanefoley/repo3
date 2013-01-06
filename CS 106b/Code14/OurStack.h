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
	int* elems;           // Pointer to elements array
	int logicalLength;    // How much space is used
	int allocatedLength;  // How much space is available
	
	void grow();          // Grows the array to increase space.
};


#endif
