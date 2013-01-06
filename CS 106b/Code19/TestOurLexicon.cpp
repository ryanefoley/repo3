/********************************************
 * File: TestOurLexicon.cpp
 *
 * A program to test our Lexicon!
 */
#include <iostream>
#include "simpio.h"
#include "OurLexicon.h"
using namespace std;

int main() {
	OurLexicon words;
	words.addWord("a");
	words.addWord("ab");
	words.addWord("about");
	words.addWord("ad");
	words.addWord("adage");
	words.addWord("adagio");
	words.addWord("bar");
	words.addWord("bard");
	words.addWord("barn");
	words.addWord("be");
	words.addWord("bed");
	words.addWord("bet");
	words.addWord("beta");
	words.addWord("can");
	words.addWord("cane");
	words.addWord("cat");
	words.addWord("dictaphone");
	words.addWord("dictation");
	words.addWord("dikdik");
	words.addWord("diktat");
	
	/* Remove a few words we don't like. */
	words.removeWord("dictaphone");
	words.removeWord("dictation");
	
	while (true) {
		/* Read some text from the user. */
		string key = getLine("Enter a search key: ");
		if (key == "") break;
		
		cout << "Is it a word?   " << boolalpha << words.containsWord(key) << endl;
		cout << "Is it a prefix? " << boolalpha << words.containsPrefix(key) << endl;
	}
	
	return 0;
}
