/* File: letters.cpp
 *
 * A function that retains just the letters in a given string.
 */
#include <iostream>
#include <cctype>
#include <string>
#include "simpio.h"
using namespace std;

/* Given a string, returns a new string holding just the
 * letters in the original string.
 */
string lettersIn(string input);

int main() {
    
	string text = getLine("Enter a string: ");
	cout << lettersIn(text) << endl;
	return 0;
}

string lettersIn(string input) {
	/* Base case: There are no letters in the empty string. */
	if (input == "") {
		return "";
	} else {
		/* If the first character is a letter, append it to the string formed by
		 * retaining just the letters in the rest of the string.
		 */
		if (isalpha(input[0])) {
			return input[0] + lettersIn(input.substr(1));
		}
		/* Otherwise, the letters in the string are just the letters in the rest
		 * of the string.
		 */
		else {
			return lettersIn(input.substr(1));
		}
	}
}




