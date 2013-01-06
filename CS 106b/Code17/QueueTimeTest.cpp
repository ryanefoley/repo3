/*****************************************************
 * File: QueueTimeTest.cpp
 *
 * A program to run stress tests of our queue.
 */
#include <iostream>
#include <ctime>
#include "OurQueue.h"
#include "queue.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int MAXIMUM_SIZE = 100000;

template <typename QueueType>
	void runTimeTrial() {

	double startTime = clock();

	QueueType Queue;
	
	/* Enqueue, then dequeue, a huge number of elements. */
	for (int elem = 0; elem < MAXIMUM_SIZE; elem++) {
		Queue.enqueue(elem);
	}
	for (int elem = 0; elem < MAXIMUM_SIZE; elem++) {
		Queue.dequeue();
	}
		
	double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
	cout << "Time to enqueue/dequeue " << MAXIMUM_SIZE << " elements: " << elapsed << "s" << endl;
}

int main() {
	runTimeTrial< OurQueue > ();
	runTimeTrial< Queue<int> >();
	
	return 0;
}
