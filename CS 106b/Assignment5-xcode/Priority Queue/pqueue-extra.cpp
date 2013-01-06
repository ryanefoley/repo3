/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */

//This is a skew heap!


#include "pqueue-extra.h"
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() {
    root = NULL;
    logicalLength = 0;
}

//A recursive function that works with the deallocation function to delete the heap.
void ExtraPriorityQueue::recDeleteTree(node* root){
    if(root == NULL) return;
    recDeleteTree(root->right);
    recDeleteTree(root->left);
    delete root;
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
    recDeleteTree(root);
}

int ExtraPriorityQueue::size() {
	return logicalLength;
}

bool ExtraPriorityQueue::isEmpty() {
	return logicalLength == 0;
}

//Merging two trees together based on skew heap design.
node* ExtraPriorityQueue::merge(node* h1, node* h2) {
    node* r = new node;
    
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;
    if(h1->value < h2->value){

        r->value = h1->value;
        r->right = h1->left;
        r->left = merge(h1->right, h2);
        return r;
    } else {
        r->value = h2->value;
        r->right = h2->left;
        r->left = merge(h2->right, h1);
        return r;
    }
}

void ExtraPriorityQueue::enqueue(string value) {
	node* newNode = new node;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    root = merge(newNode, root);
    logicalLength++;
}

string ExtraPriorityQueue::peek() {
    if(root == NULL)
        error("The heap is empty!");
	return root->value;
}

string ExtraPriorityQueue::dequeueMin() {
    if(root == NULL)
        error("The heap is empty!");
	string min = root->value;
    root = merge(root->right, root->left);
    logicalLength--;
	return min;
}

