/*****************************************************
 * File: StackSimpleTest.cpp
 *
 * A program to do simple tests of our stack.
 */
#include <iostream>
#include <ctime>
#include "OurStack.h"
#include "simpio.h"
#include "random.h"
using namespace std;


int main() {
	OurStack stack;
	for (int i = 0; i < 10; i++) {
		stack.push(i);
	}
	
	cout << "Stack has " << stack.size() << " elements." << endl;
	cout << "Top element is " << stack.top() << endl;
	
	while (!stack.isEmpty()) {
		cout << stack.pop() << " ";
	}
	cout << endl;
	
	return 0;
}
