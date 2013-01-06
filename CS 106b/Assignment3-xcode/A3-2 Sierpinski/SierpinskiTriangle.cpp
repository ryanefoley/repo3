/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the starter code for the Sierpinski Triangle problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "graphics.h"
#include "simpio.h"
using namespace std;

/* Main program */

int drawSierpinskiTriangle(int count, int order, int base, GPoint pt){ 
    
    if(count==order){ //if count is equal to order, then only draw one triangle. 
        pt = drawPolarLine(pt, base, 60);
        pt = drawPolarLine(pt, base, -60);
        drawPolarLine(pt, base, 180);
        return 0;

    }else{
        //draw triangle in bottom left corner
        base = base/2;
        GPoint pt2 = drawPolarLine(pt, base, 60);
        GPoint pt3 = drawPolarLine(pt2, base, -60);
        drawPolarLine(pt3, base, 180);
        
        //draw other triangles
        count++;
        drawSierpinskiTriangle(count, order, base, pt);
        drawSierpinskiTriangle(count, order, base, pt2);
        drawSierpinskiTriangle(count, order, base, pt3);
    }
}


int main() {
    int order = getInteger("Please enter in order of triangle to draw: "); //get order from user.
    initGraphics();
    GPoint startingPoint(0,getWindowHeight()); //get bottom left corner of window.
    drawSierpinskiTriangle(0, order, getWindowHeight(), startingPoint);
   return 0;
}
