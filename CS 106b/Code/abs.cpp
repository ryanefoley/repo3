/* File: abs.cpp
 *
 * A program that computes absolute values.
 */

#include <iostream>
#include "simpio.h" // For getInteger
using namespace std;    

/* This prototype makes it possible to use absoluteValue
 * in main even though it hasn't been defined yet.
 */
int absoluteValue(int value);

int main() {
	int value = getInteger("Enter a value: ");
	cout << "|" << value << "| = " << absoluteValue(value) << endl;
	return 0;
}

int absoluteValue(int value) {
	if (value < 0) {
		return -value;
	} else {
		return value;
	}
}










