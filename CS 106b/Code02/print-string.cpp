/* File: print-string.cpp
 *
 * A program to print a string one character at a time.
 */

#include <iostream>
#include <string>
using namespace std;

/* Prints a string one character at a time. */
void printString(string toPrint);

int main() {
	string text = "Nubian Ibex";
	printString(text);
	
	return 0;
}

void printString(string toPrint) {
	for (int i = 0; i < toPrint.length(); i++) {
		cout << toPrint[i];
	}
	cout << endl;
}




