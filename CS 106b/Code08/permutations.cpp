/* File: permutations.cpp
 *
 * A program to generate all permutations of a string.
 */

#include <iostream>
#include <string>
#include "set.h"
using namespace std;

Set<string> permutationsOf(string s);

int main() {
	foreach (string permutation in permutationsOf("xkcd")) {
		cout << permutation << endl;
	}
}

Set<string> permutationsOf(string s) {
	Set<string> result;
	/* Base case: There is just one permutation of the empty string, namely "". */
	if (s == "") {
		result += "";
	}
	/* Recursive case: For each character, permute everything but that character,
	 * then prepend the character.
	 */
	else {	
		for (int i = 0; i < s.length(); i++) {
			string iRemoved = s.substr(0, i) + s.substr(i + 1);
			foreach (string permutation in permutationsOf(iRemoved)) {
				result += s[i] + permutation;
			}
		}
	}
	return result;
}






