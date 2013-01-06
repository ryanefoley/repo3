/*****************************************************
 * File: QueueSimpleTest.cpp
 *
 * A program to do simple tests of our queue.
 */
#include <iostream>
#include <ctime>
#include "OurQueue.h"
#include "simpio.h"
#include "random.h"
using namespace std;


int main() {
	OurQueue queue;
	for (int i = 0; i < 10; i++) {
		queue.enqueue(i);
	}
	
	cout << "Queue has " << queue.size() << " elements." << endl;
	cout << "Front element is " << queue.front() << endl;
	
	while (!queue.isEmpty()) {
		cout << queue.dequeue() << " ";
	}
	cout << endl;
	
	return 0;
}
