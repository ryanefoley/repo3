/* File: subsets.cpp
 *
 * A program to list all subsets of a set.
 */
#include <iostream>
#include "set.h"
#include "vector.h"
using namespace std;

Vector< Set<int> > subsetsOf(Set<int>& s);

int main() {
	Set<int> values;
	values += 0, 1, 2, 3;
	
	foreach (Set<int> subset in subsetsOf(values)) {
		cout << subset << endl;
	}
}

Vector< Set<int> > subsetsOf(Set<int>& s) {
	if (s.isEmpty()) {
		Vector< Set<int> > result;
		result += s;
		return result;
	} else {
		int elem = s.first();
		Set<int> rest = s - elem;
		
		Vector< Set<int> > result;
		foreach (Set<int> s in subsetsOf(rest)) {
			result += s;
			result += s + elem;
		}
		
		return result;
	}
}




