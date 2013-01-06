#include "OurLexicon.h"
#include "strlib.h"
#include "error.h"
#include <cctype>        // for isalpha
using namespace std;

OurLexicon::OurLexicon() {
	root = NULL;
}

/* Recursively frees all memory used by the trie. */
void OurLexicon::recDeleteTrie(Node* node) {
	/* If there is nothing to delete, we're done. */
	if (node == NULL) return;
	
	/* Otherwise, free all children, then free this node. */
	for (int i = 0; i < 26; i++) {
		recDeleteTrie(node->children[i]);
	}
	
	delete node;
}

OurLexicon::~OurLexicon() {
	recDeleteTrie(root);
}

/* The lexicon is empty if the tree root is NULL. */
bool OurLexicon::isEmpty() {
	return root == NULL;
}

/* Counts how many words are in the trie. */
int OurLexicon::recCountWords(Node* node) {
	/* If the trie is empty, it contains no words. */
	if (node == NULL) {
		return 0;
	} else {
		/* Count how many words are in the child tries. */
		int result = 0;
		for (int i = 0; i < 26; i++) {
			result += recCountWords(node->children[i]);
		}
		
		/* Return that total, plus one if this is itself a word. */
		return node->isWord? result + 1 : result;
	}
}

int OurLexicon::size() {
	return recCountWords(root);
}

/* Determines whether a word is valid by seeing if it contains only
 * letters.
 */
void OurLexicon::checkWordIsValid(string word) {
	for (int i = 0; i < word.length(); i++) {
		if (!isalpha(word[i])) {
			error("Letters only, please!");
		}
	}
}

/* Recursively searches the trie for a node. */
OurLexicon::Node* OurLexicon::recFindNode(Node* node, string word) {
	/* If the word is empty, wherever we are - even if it's null -
	 * is the correct node.
	 */
	if (word == "") return node;
	
	/* Otherwise we are searching for something inside nothing.  This
	 * means we don't find anything.
	 */
	if (node == NULL) return NULL;
	
	/* Recursively descend into the child node. */
	int childIndex = word[0] - 'a';
	return recFindNode(node->children[childIndex], word.substr(1));
}

/* We contain a prefix if we can find some node for that prefix. */
bool OurLexicon::containsPrefix(string prefix) {
	prefix = toLowerCase(prefix);
	checkWordIsValid(prefix);
	
	return recFindNode(root, prefix) != NULL;
}

/* We contain a word if the node for that word exists and is marked
 * as a word.
 */
bool OurLexicon::containsWord(string word) {
	word = toLowerCase(word);
	checkWordIsValid(word);
	
	Node* node = recFindNode(root, word);
	return node != NULL && node->isWord;
}

/* Recursively adds a word into the trie. */
void OurLexicon::recAddWord(Node*& node, string word) {
	/* If there is no node here, go make one up. */
	if (node == NULL) {
		node = new Node;
		node->isWord = false;
		for (int i = 0; i < 26; i++) {
			node->children[i] = NULL;
		}
	}
	
	/* Base case: If the word is empty, mark this node as being
	 * a word.
	 */
	if (word == "") {
		node->isWord = true;
	}
	/* Otherwise, add the word to the appropriate subtrie. */
	else {
		int childIndex = word[0] - 'a';
		recAddWord(node->children[childIndex], word.substr(1));
	}
}

void OurLexicon::addWord(string word) {
	word = toLowerCase(word);
	checkWordIsValid(word);

	recAddWord(root, word);
}

/* Recursively removes the given word from the trie. */
void OurLexicon::recRemoveWord(Node*& node, string word) {
	/* If there is nothing here, there's nothing to remove. */
	if (node == NULL) return;
	
	/* If the word is empty, then we should mark that this is
	 * no longer a word.
	 */
	if (word == "") {
		node->isWord = false;
	}
	/* Otherwise, descend deeper into the trie. */
	else {
		int childIndex = word[0] - 'a';
		recRemoveWord(node->children[childIndex], word.substr(1));
	}
	
	/* Now, see if this node is extraneous.  If so, free it and
	 * set the incoming pointer to NULL.
	 */
	for (int i = 0; i < 26; i++) {
		/* If there is a child, we aren't extraneous.  Stay here. */
		if (node->children[i] != NULL) {
			return;
		}
	}
	
	/* We have no children.  Free this trie node. */
	delete node;
	node = NULL;
}

void OurLexicon::removeWord(string word) {
	word = toLowerCase(word);
	checkWordIsValid(word);
	
	recRemoveWord(root, word);
}


