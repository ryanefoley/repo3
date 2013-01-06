/**************************************************
 * File: structs.cpp
 *
 * A program showing off some simple properties of
 * structs.
 */
#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

/* Type: Tribute
 * A struct representing a tribute to the Hunger Games.
 */
struct Tribute {
	string name;
	int districtNumber;
};

int main() {
	Tribute* t = new Tribute;
	
	t->name = getLine("Please state your name: ");
	t->districtNumber = getInteger("From what district do you hail? ");
	
	cout << "Congratulations, " << t->name
	     << ", tribute from District " << t->districtNumber
	     << "!" << endl;
	     
	delete t;
	     
	return 0;
}


