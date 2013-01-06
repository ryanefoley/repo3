/*****************************************************
 * File: bst.cpp
 *
 * A program to play around with binary search trees!
 */
#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "simpio.h"
using namespace std;

/* Type: Node
 * A node in a binary search tree.
 */
struct Node {
	string value;
	Node* left;
	Node* right;
};

/* Searches the BST for the given value, returning a pointer to
 * the node containing that value.
 */
Node* bstFind(Node* node, string value) {
	if (node == NULL) return NULL;
	
	if (node->value == value) {
		return node;
	} else if (node->value < value) {
		return bstFind(node->right, value);
	} else {
		return bstFind(node->left, value);
	}
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

/* Recursively prints the contents of a BST. */
void printTree(Node* root) {
	if (root == NULL) return;
	
	printTree(root->left);
	cout << root->value << endl;
	printTree(root->right);
}

/* Frees memory allocated for a BST. */
void freeTree(Node* root) {
	if (root == NULL) return;
	
	freeTree(root->left);
	freeTree(root->right);
	delete root;
}

int main() {
	Node* root = NULL;
	
	while (true) {
		/* Get a value from the user; quit if it's empty. */
		string key = getLine("Enter search key: ");
		if (key == "") break;
		
		/* Check if this node already exists.  If not, add it. */
		if (bstFind(root, key) != NULL) {
			cout << key << " already exists." << endl;
		} else {
			bstInsert(root, key);
			cout << "Added: \"" << key << "\"" << endl;
		}
		
		printTree(root);
	}
	
	freeTree(root);
	
	return 0;
}





