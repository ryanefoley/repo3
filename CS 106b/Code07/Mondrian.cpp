/*
 * File: Mondrian.cpp
 * ------------------
 * This program creates a random line drawing in a style reminiscent
 * of the Dutch painter Piet Mondrian.
 */

#include <iostream>
#include <sstream>    // Needed for randomColor
#include <iomanip>    // Needed for randomColor
#include "graphics.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const double MIN_AREA = 10000;   /* Smallest square that will be split */

/* Function prototypes */

void subdivideCanvas(double x, double y, double width, double height);
string randomColor();

/* Main program */

int main() {
	while (true) {
		initGraphics();
		subdivideCanvas(0, 0, getWindowWidth(), getWindowHeight());
		getLine();
	}
	return 0;
}

/*
 * Function: subdivideCanvas
 * Usage: subdivideCanvas(x, y, width, height);
 * --------------------------------------------
 * Decomposes the specified rectangular region on the canvas recursively
 * using randomly chosen horizontal and vertical lines.  The rectangle
 * will not be split if its area is too small, and the division is always
 * chosen so that it splits the larger of the two dimensions.
 */

void subdivideCanvas(double x, double y, double width, double height) {
	if (width * height >= MIN_AREA) {
		if (randomChance(0.2)) {
			setColor(randomColor());
			fillRect(x, y, width, height);
			setColor("Black");
		} else if (width > height) {
			double mid = randomReal(0, width);
			drawLine(x + mid, y, x + mid, y + height);
			subdivideCanvas(x, y, mid, height);
			subdivideCanvas(x + mid, y, width - mid, height);
		} else {
			double mid = randomReal(0, height);
			drawLine(x, y + mid, x + width, y + mid);
			subdivideCanvas(x, y, width, mid);
			subdivideCanvas(x, y + mid, width, height - mid);
		}
      }
   }
}

/* 
 * Function: randomColor()
 * Usage: setColor(randomColor());
 * -------------------------------------------------------------------
 * Creates and returns a randomly-chosen color as a hex triplet (i.e
 * #RRGGBB.)
 */
string randomColor() {
	/* Choose three random color components. */
	int r = randomInteger(0, 255);
	int g = randomInteger(0, 255);
	int b = randomInteger(0, 255);

	/* Using the C++ ostringstream class, build up the result as a hex
	 * string.  Feel free to email me at htiek@cs.stanford.edu if you'd
	 * like a more in-depth treatment of this function!
	 */
	ostringstream result;

	/* Ensure we pad with 0s, and output in hex. */
	result << setfill('0') << hex;

	/* Build up the result. */
	result << '#' << setw(2) << r << setw(2) << g << setw(2) << b;
	return result.str();
}
