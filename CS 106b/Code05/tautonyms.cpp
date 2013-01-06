/* File: tautonyms.cpp
 *
 * A program to list all tautonyms (words consisting of two identical parts)
 * in English.
 */
 
#include <iostream>
#include <string>
#include "lexicon.h"
using namespace std;

bool isTautonym(string& word);

int main() {
	Lexicon words("EnglishWords.dat");
	
	foreach (string word in words) {
		if (isTautonym(word)) {
			cout << word << endl;
		}
	}
}

bool isTautonym(string& word) {
	if (word.length() % 2 == 1) return false;
	
	for (int i = 0; i < word.length() / 2; i++) {
		if (word[i] != word[i + word.length() / 2]) {
			return false;
		}
	}
	
	return true;
}









