/* File: anagram-clusters.cpp
 *
 * A program to find the largest anagram cluster in the English language.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "map.h"
#include "set.h"
using namespace std;

Set<string> largestAnagramClusterIn(Lexicon& words);

int main() {
	Lexicon words("EnglishWords.dat");
	
	foreach (string word in largestAnagramClusterIn(words)) {
		cout << word << endl;
	}
}

/* Given a string, returns a new string containing the letters of the
 * original string in sorted order.  This uses the "counting sort"
 * algorithm - we build up a histogram of the letter frequencies, then
 * read them back out in sorted order.
 */
string sortLetters(string& word) {
	/* Build up a frequency table of the letters. */
	Map<char, int> letterFreq;
	foreach (char ch in word) {
		letterFreq[ch]++;
	}
	
	/* Read the letters back in sorted order.  This uses the fact that the
	 * Map stores its keys sorted.
	 */
	string result;
	foreach (char ch in letterFreq) {
		for (int i = 0; i < letterFreq[ch]; i++) {
			result += ch;
		}
	}
	
	return result;
}

/* Finds the largest cluster of words in a map. */
Set<string> largestClusterIn(Map<string, Set<string> >& clusters) {
	Set<string> result;
	
	foreach (string key in clusters) {
		if (result.size() < clusters[key].size()) {
			result = clusters[key];
		}
	}
	
	return result;
}

/* Finds the largest cluster of anagrams in English. */
Set<string> largestAnagramClusterIn(Lexicon& words) {
	Map<string, Set<string> > clusters;
	
	foreach (string word in words) {
		clusters[sortLetters(word)] += word;
	}
	
	return largestClusterIn(clusters);
}








