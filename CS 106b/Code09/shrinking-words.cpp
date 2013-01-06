/* File: shrinking-words.cpp
 *
 * A program to find all the shrinkings words of length
 * 9 or more.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "vector.h"
using namespace std;

const int MIN_LENGTH = 9;

bool isShrinkableWord(string word, Lexicon& words, Vector<string>& path);

int main() {
	Lexicon words("EnglishWords.dat");
	foreach (string word in words) {
		Vector<string> path;
		if (word.length() >= MIN_LENGTH &&
		    isShrinkableWord(word, words, path)) {
			cout << word << endl;
			foreach (string step in path) {
				cout << "  " << step << endl;
			}
		}
	}
	
	return 0;
}

bool isShrinkableWord(string word, Lexicon& words, Vector<string>& path) {
	/* Base case 1: If it's not a word, it's not a shrinkable word. */
	if (!words.contains(word)) {
		return false;
	}
	/* Base case 2: If it's a word and has length one, it's shrinkable. */
	else if (word.length() == 1) {
		path += word;
		return true;
	}
	/* Otherwise, try removing each letter.  If anything we do yields a
	 * shrinkable word, we're done.
	 */
	else {
		for (int i = 0; i < word.length(); i++) {
			string iRemoved = word.substr(0, i) + word.substr(i + 1);
			if (isShrinkableWord(iRemoved, words, path)) {
				path.insertAt(0, word);
				return true;
			}
		}
	
		return false;
	}
}








