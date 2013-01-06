/* File: reverse.cpp
 *
 * Code to recursively reverse a string.
 */
#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

string reverseString(string line);

int main() {
	string line = getLine("Enter a string: ");
	cout << reverseString(line) << endl;
}

string reverseString(string line) {
	/* The reverse of the empty string is itself. */
	if (line == "") {
		return "";
	}
	/* Otherwise, reverse the latter part of the string, then append the first
	 * character to it.
	 */
	else {
		return reverseString(line.substr(1)) + line[0];
	}
}


