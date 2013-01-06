//
//  PathfinderGraph.h
//  Pathfinder
//
//  Created by Ryan Foley on 6/5/12.
//  Copyright (c) 2012 Stanford. All rights reserved.
//

#ifndef Pathfinder_PathfinderGraph_h
#define Pathfinder_PathfinderGraph_h

#include "graphtypes.h"

using namespace std;

class PathfinderGraph {
public:
	PathfinderGraph();
	~PathfinderGraph();
	
	/* Adds a node to the graph. */
	void addNode(string name, int x, int y);
    
    /* Adds an arc to the graph. */
	void addArc(string start, string finish, int dist);
    
    /* Returns the set of Nodes in the graph */
    Set<Node*> getNodes();
    
    /* Returns the set of Arcs in the graph */
    Set<Arc*> getArcs();
    
    /* A function that returns the total number of nodes in the graph. */
    int numberNodes();
    
    /* Function that removes all the nodes and arcs from the graph */
    void clear();
	
	
private:
    SimpleGraph graph;
    int nNodes;
    int nArcs;
    
};    

#endif
