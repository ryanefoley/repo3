//
//  PathfinderGraph.cpp
//  Pathfinder
//
//  Created by Ryan Foley on 6/5/12.
//  Copyright (c) 2012 Stanford. All rights reserved.
//

#include <iostream>
#include "PathfinderGraph.h"
#include "graphtypes.h"

using namespace std;

PathfinderGraph::PathfinderGraph() {
    nNodes = 0;
    nArcs = 0;
    
}

PathfinderGraph::~PathfinderGraph() {
    
    if(!graph.nodes.isEmpty()){
        foreach(Node* node in graph.nodes)
        delete node;
    }

    if(!graph.arcs.isEmpty()){
        foreach(Arc* arc in graph.arcs)
        delete arc;
    }    
}

/* Adds a node to the graph. */
void PathfinderGraph::addNode(string name, int x, int y){
    Node* node = new Node;
    node -> name = name;
    GPoint pt(x, y);
    node -> loc = pt; 
    
    graph.nodes += node;
    nNodes++;
    graph.nodeMap[node->name] = node;
}

 /* Adds an arc to the graph. */
void PathfinderGraph::addArc(string start, string finish, double cost){
    Arc* arc = new Arc;
    arc -> start = graph.nodeMap[start];
    arc -> finish = graph.nodeMap[finish];
    arc -> cost = cost;
    
    graph.arcs += arc;
    nArcs++;
}

/* Returns the set of Nodes in the graph */
Set<Node*> PathfinderGraph::getNodes(){
    return graph.nodes;
}

/* Returns the set of Arcs in the graph */
Set<Arc*> PathfinderGraph::getArcs(){
    return graph.arcs;
}


/* A function that returns the total number of nodes in the graph. */
int PathfinderGraph::numberNodes(){
    return nNodes;
}

/* A function that returns the total number of arcs in the graph. */
int PathfinderGraph::numberArcs(){
    return nArcs;
}

/* Function that removes all the nodes and arcs from the graph */
void PathfinderGraph::clear(){
    graph.nodes.clear();
    graph.arcs.clear();
    graph.nodeMap.clear();
    nNodes = 0;
    nArcs = 0;
}


