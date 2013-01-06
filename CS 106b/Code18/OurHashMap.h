/****************************************************
 * File: OurHashMap.h
 *
 * A HashMap class that implements a map from strings
 * to integers.
 */
#ifndef OurHashMap_Included
#define OurHashMap_Included

#include <string>
using namespace std;

class OurHashMap {
public:
	/* Constructs a map with the specified number of buckets. */
	OurHashMap(int numBuckets = 101);
	
	/* Cleans up memory from the HashMap. */
	~OurHashMap();
	
	/* Inserts a key/value pair into the HashMap. */
	void put(string key, int value);
	
	/* Determines whether a given key exists in the map. */
	bool containsKey(string key);
	
	/* Returns the value associated with a given key.  If the
	 * key is not found, signals an error.
	 */
	int get(string key);
	
	/* Returns how many elements are in the map. */
	int size();
	
	/* Returns whether the map is empty. */
	bool isEmpty();

private:
	int numElems;
	int numBuckets;
	
	struct Cell {
		string key;
		int value;
		
		Cell* next;
	};
	
	Cell** buckets;
};


#endif
