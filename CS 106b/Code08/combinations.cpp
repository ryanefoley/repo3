/* File: combinations.cpp
 *
 * A program to list all combinations of a set.
 */
#include <iostream>
#include "set.h"
#include "vector.h"
using namespace std;

Vector< Set<int> > combinationsOf(Set<int>& s, int n);

int main() {
	Set<int> values;
	values += 0, 1, 2, 3, 4, 5, 6;
	
	foreach (Set<int> subset in combinationsOf(values, 3)) {
		cout << "{ ";
		foreach (int num in subset) {
			cout << num << " ";
		}
		cout << "}" << endl;
	}
}

Vector< Set<int> > combinationsOf(Set<int>& s, int n) {
	/* Base case 1: There is one way to pick zero elements out of a set. */
	if (n == 0) {
		Vector< Set<int> > singletonResult;
		Set<int> emptySet;
		singletonResult += emptySet;
		return singletonResult;
	}
	/* Base case 2: We cannot pick n > 0 elements out of an empty set. */
	else if (s.isEmpty()) {
		Vector< Set<int> > emptyResult;
		return emptyResult;
	}
	/* Recursive case: We single out some element 'elem'.  Every combination of
	 * n elements either
	 *
	 *   1. Doesn't include elem, and is an n-element subset of what remains, or
	 *   2. Does include elem, and is an (n-1) element subset of what remains.
	 */
	else {
		/* Single out some element. */
		int elem = s.first();
		Set<int> rest = s - elem;
	
		/* Get all combinations NOT including that element. */
		Vector< Set<int> > result = combinationsOf(rest, n);
		
		/* Get (n-1)-element combinations of what remains, then add this singled
		 * out element back in.
		 */
		foreach (Set<int> combination in combinationsOf(rest, n - 1)) {
			result += combination + elem;
		}
		
		return result;
	}
}




