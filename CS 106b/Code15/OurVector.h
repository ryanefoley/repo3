/******************************************************
 * File: OurVector.h
 *
 * Our own custom implementation of the Vector type!
 */
#ifndef OurVector_Included
#define OurVector_Included

class OurVector {
public:
	// Constructor / Destructor
	OurVector(int startSize = 0);
	~OurVector();
	
	// size
	int size();
	
	// is empty
	bool isEmpty();
	
	// insert
	void insertAt(int value, int index);
	void append(int value);
	
	// remove
	void removeAt(int index);
	
	// get
	int getAt(int index);
	
	/* We didn't end up implementing these.  As a fun exercise, try doing
	 * this yourself!
	 */
	// reverse
	// clear
	// contains / indexOf
	// sort
	// find median
	// biggest / smallest / coolest
	// swap
	// set


private:
	int* elems;
	int logicalLength;
	int allocatedLength;

	void grow();
};

/* This function can be implemented externally to the Vector. */
bool contains(OurVector& v, int value);


#endif
