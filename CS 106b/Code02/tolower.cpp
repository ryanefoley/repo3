/* File: tolower.cpp
 *
 * A program to convert a string to lower case.
 */
#include <iostream>
#include <string>
#include <cctype>
#include "simpio.h"
using namespace std;

string toLowerCase(string line);

int main() {
	string line = getLine("Enter a string: ");
	cout << toLowerCase(line) << endl;
}

string toLowerCase(string line) {
	for (int i = 0; i < line.length(); i++) {
		line[i] = tolower(line[i]);
	}
	return line;
}


