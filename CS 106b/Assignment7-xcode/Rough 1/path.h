/*
 * File: path.h
 * ------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the interface for a Path class that encapsulates
 * the idea of a multistep path.
 */

/////////////////////////////////////////////////////////////////////
// Your task in this part of the assignment is to design a Path    //
// class that supports the implementation of Dijkstra's algorithm. //
// As noted in the assignment handout, your class must meet the    //
// following conditions:                                           //
//                                                                 //
// 1. The class must not export any public instance variables.     //
//    All data required to store the path must be private to the   //
//    class.                                                       //
//                                                                 //
// 2. The method that returns the total cost of the path must      //
//    run in constant time.                                        //
//                                                                 //
// 3. The class must export a toString method that returns a       //
//    string composed of the nodes on the path separated by        //
//    arrows formed by the two-character sequence ->.              //
//                                                                 //
// 4. Any heap storage allocated by this class must be freed       //
//    when the object is deleted.                                  //
//                                                                 //
// Beyond those restrictions, you are free to design and implement //
// this class as you see fit.  You must, however, document your    //
// design decisions in the corresponding path.cpp file.            //
/////////////////////////////////////////////////////////////////////

#ifndef _path_h
#define _path_h

#include "graphtypes.h"

class Path {
public:
    Path();
    ~Path();
        
    /* Adds an arc to the path. */
    void addArc(Arc* arc);
    
    /* Returns the total cost of the path */
    int totalCost();
    
    /* Returns the string of all the names of the nodes in the path seperated by "->" */
    string toString();
    
    /* Function that removes the last Arc from the Path */
    void removeLast();
    
    /* A function that gets the arc in the Path at position pos. */
    Arc* getArc(int pos);

    /* A function that removes all the arcs from the Path. */
    void clear();
    
    /* A function to return the number of arcs in the path. */
    int numArcs();
    
        
    /* Here I used a vector for the path because it was simple to use and 
     * had no apparent disadvantages. Also, the instance variable cost will
     * allow us to keep track of the total cost of the path as we add arcs.
     */
private:
    Vector<Arc*> path; 
    int cost;
};

#endif
