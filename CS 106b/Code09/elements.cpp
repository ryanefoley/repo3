/* File: elements.cpp
 *
 * A program to determine whether a word can be written using just the
 * chemical elements.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "map.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* The maximum length of any element symbol. */
const int MAX_ELEM_LENGTH = 3;

/* Returns a map associating lower-case representations of element symbols with
 * their properly-capitalized selves.
 */
Map<string, string> elementSymbols();

/* Given a string and a map of the elements, returns whether the string can be
 * spelled with just element symbols.  If so, result is updated to be the
 * spelled version of that string.
 */
bool isElementSpellable(string s, Map<string, string>& elements,
                        string& result);

int main() {
	/* Load the element symbols into a Map. */
	Map<string, string> elements = elementSymbols();

	while (true) {
		string text = getLine("Enter a word: ");
		string result;
		if (isElementSpellable(text, elements, result)) {
			cout << result << endl;
		} else {
			cout << "Sorry, I can't spell that one out." << endl;
		}
	}
}

/* Loads a map of element symbols from a file. */
Map<string, string> elementSymbols() {
	Map<string, string> result;
	ifstream input("chemical-elements.txt");
	
	while (true) {
		string line;
		getline(input, line);
		
		if (input.fail()) return result;
		
		/* Convert the symbols to lower-case. */
		result[toLowerCase(line)] = line;
	}
}

bool isElementSpellable(string text, Map<string, string>& elements,
                        string& result) {
	/* Base case: The empty string is spellable. */
	if (text == "") {
		result = "";
		return true;
	} else {
		/* Determine the longest legal prefix we can munch off. */
		int longestPrefix = text.length();
		if (longestPrefix > MAX_ELEM_LENGTH) {
			longestPrefix = MAX_ELEM_LENGTH;
		}
	
		/* Try each prefix. */
		for (int i = 1; i <= longestPrefix; i++) {
			string prefix = toLowerCase(text.substr(0, i));
			
			/* If this prefix is valid and the rest is shrinkable, we're done. */
			if (elements.containsKey(prefix) &&
			    isElementSpellable(text.substr(i), elements, result)) {
			    result = elements[prefix] + result;
			 	return true;   
			}
		}
		
		return false;
	}
}



