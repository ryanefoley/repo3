#include "OurHashMap.h"
#include "error.h"
using namespace std;

/* * * * * Helper Functions * * * * */

/* 
 * Function hashCode
 * Usage: int code = hashCode(key)
 * ---------------------------------------------------------
 * An hash function for strings. Adapted from code online at
 * http://www.daniweb.com/software-development/cpp/threads/231987/string-hash-function
 * This function is called a SAX hash function (Shift-Add-XOR) and is
 * great at distributing strings evenly.
 */
const int HASH_MASK = unsigned(-1) >> 1;
int hashCode(string key) {
    int hashVal = 0;
    for (int x = 0; x < key.length(); ++x) {
        hashVal ^= (hashVal << 5) +
                   (hashVal >> 2) +
                   key[x];
    }
    return hashVal & HASH_MASK;
}

/* * * * * Implementation of OurHashMap. * * * * */

const int MIN_BUCKETS = 7;

OurHashMap::OurHashMap(int numBuckets) {
	/* Initially, we have no elements. */
	numElems = 0;
	
	/* Set the number of buckets to either the user's value or NUM_BUCKETS,
	 * whichever is larger.
	 */
	this->numBuckets = max(MIN_BUCKETS, numBuckets);
	
	/* Allocate and zero-out the buckets. */
	buckets = new Cell*[this->numBuckets];
	for (int i = 0; i < this->numBuckets; i++) {
		buckets[i] = NULL;
	}
}

OurHashMap::~OurHashMap() {
	/* Free each linked list. */
	for (int i = 0; i < numBuckets; i++) {
		while (buckets[i] != NULL) {
			Cell* next = buckets[i]->next;
			delete buckets[i];
			buckets[i] = next;
		}
	}
	
	/* Free the top-level list. */
	delete[] buckets;
}

int OurHashMap::size() {
	return numElems;
}

bool OurHashMap::isEmpty() {
	return size() == 0;
}

void OurHashMap::put(string key, int value) {
	/* Check if the element is already here. */
	int bucket = hashCode(key) % numBuckets;
	for (Cell* curr = buckets[bucket]; curr != NULL; curr = curr->next) {
		if (curr->key == key) {
			curr->value = value;
			return;
		}
	}
	
	/* Guess it isn't!  Allocate a new cell and chain it in. */
	Cell* cell = new Cell;
	cell->value = value;
	cell->key = key;
	
	cell->next = buckets[bucket];
	buckets[bucket] = cell;
	
	numElems++;
}

bool OurHashMap::containsKey(string key) {
	/* Look just in the bucket for this key. */
	int bucket = hashCode(key) % numBuckets;
	for (Cell* curr = buckets[bucket]; curr != NULL; curr = curr->next) {
		if (curr->key == key) {
			return true;
		}
	}
	
	return false;
}

int OurHashMap::get(string key) {
	/* Look just in the bucket for this key. */
	int bucket = hashCode(key) % numBuckets;
	for (Cell* curr = buckets[bucket]; curr != NULL; curr = curr->next) {
		if (curr->key == key) {
			return curr->value;
		}
	}
	
	error("We don't know anyone by the name " + key);
}






