/***************************************************
 * File: OurLexicon.h
 *
 * An implementation of the Lexicon backed by a trie.
 */
#ifndef OurLexicon_Included
#define OurLexicon_Included

#include <string>
using namespace std;

class OurLexicon {
public:
	OurLexicon();
	~OurLexicon();
	
	/* Returns whether the lexicon is empty. */
	bool isEmpty();
	
	/* Returns the number of words in the lexicon. */
	int size();
	
	/* Adds a word to the lexicon. */
	void addWord(string word);
	
	/* Returns whether the given word is contained in the lexicon. */
	bool containsWord(string word);
	
	/* Returns whether the given prefix is contained in the lexicon. */
	bool containsPrefix(string word);
	
	/* Removes a word from the lexicon, if it exists. */
	void removeWord(string word);

private:
	struct Node {
		bool isWord;
		Node* children[26];
	};
	Node* root;
	
	/* Recursively counts how many words there are. */
	int recCountWords(Node* node);
	
	/* Determines whether an input word is valid for our trie. */
	void checkWordIsValid(string word);
	
	/* Searches the trie for the node corresponding to a word,
	 * returning it if found and NULL otherwise.
	 */
	Node* recFindNode(Node* node, string word);
	
	/* Inserts a new word into the trie. */
	void recAddWord(Node*& node, string word);
	
	/* Removes a word from the trie. */
	void recRemoveWord(Node*& node, string word);
	
	/* Frees all memory allocated by the trie. */
	void recDeleteTrie(Node* node);
};


#endif
