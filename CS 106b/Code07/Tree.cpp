/*
 * File: Tree.cpp
 * -------------------
 * This program draws a fractal tree.  It's very pretty!
 */

#include <iostream>
#include <cmath>
#include "graphics.h"
#include "gtypes.h"
#include "random.h"

/* The depth of the tree. */
const int MAX_DEPTH = 10;

/* Colors for each branch level. */
const string TREE_COLORS[] = {
	"#202000",
	"#402000",
	"#603000",
	"#804000",
	"#705000",
	"#606000",
	"#507000",
	"#408000",
	"#309000",
	"#20A000"
};

/* Function prototypes */

void drawTree(double x, double y, double r, double theta, int depth);

/* Main program */

int main() {
	initGraphics();

	/* Draw a tree rooted at the bottom-center, whose height is the height of the
	 * window and is initially pointing up.
	 */
	drawTree(getWindowWidth() / 2.0, getWindowHeight(), getWindowHeight(), 90.0, 0);

	return 0;
}

void drawTree(double x, double y, double r, double theta, int depth) {
	if (depth < MAX_DEPTH) {
		double growth = randomReal(0.1, 0.4);
		setColor(TREE_COLORS[depth]);
		
		GPoint branchPt = drawPolarLine(x, y, r * growth, theta);
		
		int numChildren = randomInteger(2, 8);
		for (int i = 0; i < numChildren; i++) {
			double thetaPrime = theta + randomReal(-45, +45);
			drawTree(branchPt.getX(), branchPt.getY(), (1.0 - growth) * r, thetaPrime, depth + 1);
		}
	}
}
