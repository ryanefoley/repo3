/* File: list-strings.cpp
 *
 * A program to list all strings of the letters A, B, and C
 * of length at most four.
 */
#include <iostream>
#include "queue.h"
using namespace std;

Queue<string> stringsOfLengthAtMost(int maxSize);

int main() {
	Queue<string> words = stringsOfLengthAtMost(6);
	while (!words.isEmpty()) {
		cout << '"' << words.dequeue() << "\" ";
	}
	
	cout << endl;	
	return 0;
}

Queue<string> stringsOfLengthAtMost(int maxSize) {
	Queue<string> result;
	
	Queue<string> worklist;
	worklist.enqueue("");
	
	while (!worklist.isEmpty()) {
		string curr = worklist.dequeue();
		result.enqueue(curr);
	
		if (curr.length() < maxSize) {
			worklist.enqueue(curr + 'A');
			worklist.enqueue(curr + 'B');
			worklist.enqueue(curr + 'C');
		}
	}
	
	return result;
}









						
