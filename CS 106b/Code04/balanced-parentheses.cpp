/* File: balanced-parentheses.cpp
 *
 * A program to check if a string has balanced parentheses.
 */
#include <iostream>
#include <string>
#include "simpio.h"
#include "stack.h"
using namespace std;

bool hasBalancedParentheses(string text);

int main() {
	while (true) {
		string text = getLine("Enter a string: ");
		if (hasBalancedParentheses(text)) {
			cout << "Balanced!" << endl;
		} else {
			cout << "Not balanced!" << endl;
		}
	}
}

bool isOpenParenthesis(char ch) {
	return ch == '(' || ch == '[' || ch == '{';
}

bool isCloseParenthesis(char ch) {
	return ch == ')' || ch == ']' || ch == '}';
}

bool isMatchingParenthesis(char open, char close) {
	if (open == '(')
		return close == ')';
	else if (open == '[')
		return close == ']';
	else if (open == '{')
		return close == '}';
	else
		return false;
}

bool hasBalancedParentheses(string text) {
	Stack<char> parens;
	
	for (int i = 0; i < text.length(); i++) {
		if (isOpenParenthesis(text[i])) {
			parens.push(text[i]);
		} else if (isCloseParenthesis(text[i])) {
			if (parens.isEmpty()) {
				return false;
			}
			
			if (!isMatchingParenthesis(parens.pop(), text[i])) {
				return false;
			}	
		}	
	}
	
	// (((((((((((((((((((((((((((((((((((((((((((((((((((
	return parens.isEmpty();
}





