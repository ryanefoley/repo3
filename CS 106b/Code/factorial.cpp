/* File: factorial.cpp
 *
 * A program that computes n! recursively.
 */

#include <iostream>
#include "simpio.h"
using namespace std;

/* Computes n!. */
int factorial(int n);

int main() {
	int num = getInteger("Enter a number: ");
    cout << num << "! = " << factorial(num) << endl;
    return 0;
}

/* This implementation of factorial is based on the following
 * recursive decomposition:
 *
 *   0! = 1
 *   n! = n * (n - 1)!
 */
int factorial(int n) {
    if (n == 0) {
    	return 1;
    } else {
    	return n * factorial(n - 1);
    }
}










