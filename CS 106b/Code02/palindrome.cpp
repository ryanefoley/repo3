/* File: palindrome.cpp
 *
 * A program that checks whether or not a string is a palindrome.
 */
#include <iostream>
#include <string>
#include <cctype>
#include "simpio.h"
using namespace std;

string toLowerCase(string input);
string reverseString(string input);
string lettersIn(string input);
bool isPalindrome(string input);

int main() {
	string line = getLine("Enter a string: ");
	if (isPalindrome(line)) {
		cout << "That's a palindrome!" << endl;
	} else {
		cout << "Nope, it's not a palindrome." << endl;
	}
	
	return 0;
}

bool recIsPalindrome(string input) {
	/* Any length-0 or length-1 string is a palindrome. */
	if (input.length() <= 1) {
		return true;
	} else {
		/* If the first and last characters don't match, this cannot be a
		 * palindrome.
		 */
		if (input[0] != input[input.length() - 1])
			return false;
		
		/* This is a palindrome precisely if the middle characters are. */
		return recIsPalindrome(input.substr(1, input.length() - 2));
	}
}

bool isPalindrome(string input) {
	input = toLowerCase(lettersIn(input));
	return recIsPalindrome(input);
}

string toLowerCase(string input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = tolower(input[i]);
	}
	return input;
}

string reverseString(string input) {
	if (input == "") {
		return "";
	} else {
		return reverseString(input.substr(1)) + input[0];
	}
}

string lettersIn(string input) {
	if (input == "") {
		return "";
	} else {
		if (isalpha(input[0])) {
			return input[0] + lettersIn(input.substr(1));
		} else {
			return lettersIn(input.substr(1));
		}
	}
}

