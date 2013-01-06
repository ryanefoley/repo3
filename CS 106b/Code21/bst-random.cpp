/*****************************************************
 * File: bst-random.cpp
 *
 * A program to generate and explore a large, random
 * binary search tree.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "vector.h"
#include "simpio.h"
#include "random.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
	string value;
	Node* left;
	Node* right;
};

/* Generates a random string of the given length. */
string randomString(int length = 16) {
	string result;
	for (int i = 0; i < length; i++) {
		result += char(randomInteger('A', 'Z'));
	}
	return result;
}

/* Inserts a value into the BST. */
void bstInsert(Node*& node, string value) {
	if (node == NULL) {
		node = new Node;
		node->value = value;
		node->left = node->right = NULL;
	} else if (node->value == value) {
		return;
	} else if (node->value < value) {
		bstInsert(node->right, value);
	} else {
		bstInsert(node->left, value);
	}
}

/* Frees memory allocated for a BST. */
void freeTree(Node* root) {
	if (root == NULL) return;
	
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

/* Returns the height of a BST. */
int treeHeight(Node* root) {
	if (root == NULL) return 0;
	
	return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

/* Constant controlling how many nodes should be added to our random tree. */
const int NUM_NODES = 1000000;

int main() {
	/* Construct a large, random BST. */
	Node* root = NULL;
	for (int i = 0; i < NUM_NODES; i++) {
		bstInsert(root, randomString());	
	}
	
	/* Print out the height of that tree. */
	cout << "Tree height for " << NUM_NODES << " nodes: " << treeHeight(root) << endl;	
	
	return 0;
}





