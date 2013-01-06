/*****************************************************
 * File: bst.cpp
 *
 * A program to play around with binary search trees!
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
 * A node in a binary search tree.  This particular node structure is for
 * a treap.
 */
struct Node {
	string value;
	double priority;
	Node* left;
	Node* right;
};

/* Pulls the left child of the given node above the root. */
void rotateRight(Node*& root) {
	if (root == NULL || root->left == NULL) {
		error("You can't rotate that tree.");
	}
	
	Node* leftChild = root->left;
	root->left = leftChild->right;
	leftChild->right = root;
	root = leftChild;
}

/* Pulls the right child of the given node above the root. */
void rotateLeft(Node*& root) {
	if (root == NULL || root->right == NULL) {
		error("You can't rotate that tree.");
	}
	
	Node* rightChild = root->right;
	root->right = rightChild->left;
	rightChild->left = root;
	root = rightChild;
}

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
		node->priority = randomReal(0, 1);
	} else if (node->value == value) {
		return;
	} else if (node->value < value) {
		bstInsert(node->right, value);
		
		/* Treap step: Rotate this node up if it is in the wrong place. */
		if (node->right->priority > node->priority) {
			rotateLeft(node);
		}
	} else {
		bstInsert(node->left, value);
		
		/* Treap step: Rotate this node up if it is in the wrong place. */
		if (node->left->priority > node->priority) {
			rotateRight(node);
		}
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

/* Returns the height of a BST. */
int treeHeight(Node* root) {
	if (root == NULL) return 0;
	
	return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

int main() {
	Node* root = NULL;
	
	/* Generates a random treap of 10,000 words and prints the height.
	 * In a normal BST, this would have height 10,000.
	 */
	string word;
	for (int i = 0; i < 10000; i++) {
		bstInsert(root, word);
		word += 'A';
	}
	
	cout << "Tree height: " << treeHeight(root) << endl;
	
	freeTree(root);
	
	return 0;
}







