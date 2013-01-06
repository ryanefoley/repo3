/*
 * File: path.cpp
 * --------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file implements the path.h interface.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to write the code   //
// that implements your path.h interface.  For the benefit of      //
// future programmers who will need to work on this interface,     //
// you must also write an extended comment (presumably replacing   //
// this to-do box) that documents the design decisions you made    //
// in structuring the Path class as you did.                       //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "path.h"
#include "graphtypes.h"

using namespace std;

Path::Path(){
    Vector<Arc*> path;
}

Path::~Path(){
}

/* Adds an arc to the path. */
void Path::addArc(Arc* arc){
    path += arc;
    cost += arc->cost;
}

/* Returns the total cost of the path */
double Path::totalCost(){
    return cost;
}

/* Returns the string of all the names of the nodes in the path seperated by "->" */
string Path::toString(){
    string result = "";
    for(int i = 0; i < path.size(); i++){
        result = result + path[i]->start->name + " -> "; //append name of each starting node plus the ->
    }
    result += path[path.size()-1]->finish->name; //append last node name
    return result;
}

/* A function that removes all the last arc from the path. */
void Path::removeLast(){
    cost -= path[path.size()-1]->cost;
    path.removeAt(path.size()-1);
}

/* A function that gets the last arc in the Path without removing it. */
Arc* Path::getArc(int pos){
    return path[pos];
}

/* A function that removes all the arcs from the Path. */
void Path::clear(){
    path.clear();
    cost = 0;
}

/* A function to return the number of arcs in the path. */
int Path::numArcs(){
    return path.size();
}




