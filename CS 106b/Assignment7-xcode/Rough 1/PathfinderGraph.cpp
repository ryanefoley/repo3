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

void PathfinderGraph::addNode(string name, int x, int y){
    Node* node = new Node;
    node -> name = name;
    GPoint pt(x, y);
    node -> loc = pt; 
    
    graph.nodes += node;
    nNodes++;
    graph.nodeMap[node->name] = node;
}

void PathfinderGraph::addArc(string start, string finish, int cost){
    Arc* arc = new Arc;
    arc -> start = graph.nodeMap[start];
    arc -> finish = graph.nodeMap[finish];
    arc -> cost = cost;
    
    graph.arcs += arc;
    nArcs++;
}

Set<Node*> PathfinderGraph::getNodes(){
    return graph.nodes;
}

Set<Arc*> PathfinderGraph::getArcs(){
    return graph.arcs;
}


/* A function that returns the total number of nodes in the graph. */
int PathfinderGraph::numberNodes(){
    return nNodes;
}

void PathfinderGraph::clear(){
    graph.nodes.clear();
    graph.arcs.clear();
    graph.nodeMap.clear();
    nNodes = 0;
    nArcs = 0;
}


