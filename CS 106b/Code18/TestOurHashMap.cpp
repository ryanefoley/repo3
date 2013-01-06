/********************************************
 * File: TestOurHashMap.cpp
 *
 * A program to test our HashMap!
 */
#include <iostream>
#include "simpio.h"
#include "OurHashMap.h"
using namespace std;

int main() {
	OurHashMap map;
	
	while (true) {
		/* Read some text from the user. */
		string key = getLine("Enter a search key: ");
		
		/* Count how many times we've seen it. */
		int lookupTimes = 0;
		if (map.containsKey(key)) {
			lookupTimes = map.get(key);
		}
		
		cout << "You've looked that up " << lookupTimes
		     << " time" << (lookupTimes == 1? "" : "s")
		     << " before." << endl;
		
		/* Update the map. */     
		map.put(key, lookupTimes + 1);
	}
}
