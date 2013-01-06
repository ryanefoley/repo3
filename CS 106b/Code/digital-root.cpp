/* File: digital-roots.cpp
 *
 * A program to compute digital roots.  The digital root of a
 * number is the number resulting from repeatedly summing the
 * digits of the number until a single digit is reached.  For
 * example:
 *
 *   digitalRoot(5) = 5
 *   digitalRoot(42) = 4 + 2 = 6
 *   digitalRoot(137) = digitalRoot(1 + 3 + 7) = digitalRoot(11) = 2
 */
#include <iostream>
#include "simpio.h"
using namespace std;

/* Computes the digital root of its input. */
int digitalRoot(int value);

/* Returns the sum of the digits in a number. */
int sumOfDigits(int value);

int main() {
	while (true) {
		int value = getInteger("Enter an integer: ");
		cout << value << " has digital root " << digitalRoot(value) << endl;
	}
}

/* This implementation of digital roots is based on the following
 * recursive decomposition:
 *
 *  - The digital root of a one-digit number is that number itself.
 *  - The digital root of a multi-digit number is the same as the
 *      digital root of the sum of the digits of the number.
 */
int digitalRoot(int value) {
	/* Base case: The digital root of a single digit is that digit. */
	if (value < 10) {
		return value;
	} 
	/* Recursive step: The digital root of a larger number is the same
	 * as the digital root of the sum of the number's digits.
	 */
	else {
		return digitalRoot(sumOfDigits(value));
	}
}

/* This implementation of the sum of the digits of a number is based
 * on the following recursive decomposition:
 *
 *   - The sum of a number with no digits left is 0.
 *   - The sum of a number with at least one digit is the sum of
 *        the last digit and the sum of the first digits of the number.
 */
int sumOfDigits(int value) {
	/* Base case: If there are no digits left, the sum is 0. */
	if (value == 0) {
		return 0;
	}
	/* Recursive step: Tear the last digit off of the number, then
	 * add that value to the sum of the remaining digits.
	 */
	else {
		return sumOfDigits(value / 10) + (value % 10);
	}
}










