#include "RandomBag.h"
#include "error.h"
#include "random.h"
#include <string>
using namespace std;

int RandomBag::size() {
	return elems.size();
}

bool RandomBag::isEmpty() {
	return elems.isEmpty();
}

void RandomBag::add(int value) {
	elems += value;
}

int RandomBag::removeRandom() {
	if (isEmpty()) {
		error("You can't make something from nothing.");
	}
	
	int index = randomInteger(0, size() - 1);
	int result = elems[index];
	elems.removeAt(index);
	
	return result;
}




