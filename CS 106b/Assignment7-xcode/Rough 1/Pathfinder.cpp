/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// [TODO: complete this implementation]

#include <iostream>
#include <string>
#include "console.h"
#include "graphtypes.h"
#include <cctype>
#include "gpathfinder.h"
#include "PathfinderGraph.h"
#include <string>
#include "simpio.h" //for getLine
#include "console.h"
#include "strlib.h" //for upper and lowercase functions
#include "tokenscanner.h"
#include "foreach.h"
#include "pqueue.h"
#include "path.h"
using namespace std;

/* Function prototypes */

void quitAction();

void promptUserForFile(ifstream& mapData) {
    while (true) {
        //get filename from user and open the file.
        cout << "Please enter filename containing map data: " << endl;
        string filename;
        getline(cin, filename); 
        mapData.open(filename.c_str()); 
        //send an error if cannot open the file and try again.
        if (!mapData.fail()) return;
        mapData.clear();
        cout << "Unable to open that file.  Try again." << endl;
    } 
}

void getNodes(PathfinderGraph& graph, ifstream& mapData){
    while(true){
        string line;
        getline(mapData, line);
        if(line == "ARCS") break; //We have reached the list of Arcs so there are no more Nodes to get.
        
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        
        //get the city name - the first word in the line
        string city = scanner.nextToken();
        
        scanner.scanNumbers();
        //get the x and y coordinates, the next two numbers.
        string next = scanner.nextToken();
        int x = stringToInteger(next);
        next = scanner.nextToken();
        int y = stringToInteger(next);
        
        graph.addNode(city, x, y);
    }
}

void getArcs(PathfinderGraph& graph, ifstream& mapData){
    while(true){
        if(mapData.get() == EOF) break;
        else mapData.unget();
        
        string line;
        getline(mapData, line);
            
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        
        string start = scanner.nextToken();
        string finish = scanner.nextToken();
        
        scanner.scanNumbers();
        string next = scanner.nextToken();
        int cost = stringToInteger(next);

        graph.addArc(start, finish, cost);
        graph.addArc(finish, start, cost);
    }
}

/* A function that fills the set of Arcs in each Node that are the Arcs from that Node. */
void fillArcsInNodes(PathfinderGraph& graph){
    foreach(Arc* arc in graph.getArcs()){
        foreach(Node* node in graph.getNodes()){
            if(arc->start == node) node->arcs += arc;
        }
    }
}

void readFile(PathfinderGraph& graph, ifstream& mapData){
    //Get the first line which corresponds to the name of the image file for the map.
    string imageFileName;
    getline(mapData, imageFileName);
    drawPathfinderMap(imageFileName);
    
    //Get next line which should be the word NODES
    string line;
    getline(mapData, line);
    if(line != "NODES") error("Wrong file format");
    
    //Get all of the Nodes and Arcs from the file.
    getNodes(graph, mapData);
    getArcs(graph, mapData);
    fillArcsInNodes(graph); //Filling the set of Arcs in each Node that are the Arcs from that Node.
}

void drawMap(PathfinderGraph& graph){
    foreach(Node* node in graph.getNodes())
    drawPathfinderNode(node->loc, NODE_COLOR, node->name);
    foreach(Arc* arc in graph.getArcs())
    drawPathfinderArc(arc->start->loc, arc->finish->loc, ARC_COLOR);
}

void mapAction(PathfinderGraph& graph){
    ifstream mapData;
    graph.clear();
    promptUserForFile(mapData); 
    repaintPathfinderDisplay();
    readFile(graph, mapData);
    drawMap(graph);
}


//Function for use with defineClickListener in getNodeFromClick
void assignGPoint(GPoint clickPt, GPoint& pt){
    pt = clickPt;
}

Node* getNodeFromClick(bool start, PathfinderGraph& graph){
    if(start) cout << "Click on starting location... " << endl;
    else cout << "Click on finishing location... " << endl;
    
    GPoint pt = getMouseClick();
    double x = pt.getX();
    double y = pt.getY();
    
    Set<Node*> nodes = graph.getNodes();
    
    foreach(Node* node in nodes){
        if(node == NULL){
            cout << "Node is null\n";
            continue;
        } 
        if(node->name == ""){
            cout << "Node->name is null\n";
            continue;
        }
        double nodeX = node->loc.getX();
        double nodeY = node->loc.getY();
        
        //Made node radius slightly larger to make a little easier to click.
        if(((x - nodeX)*(x - nodeX) + (y - nodeY)*(y - nodeY)) <= 2*(NODE_RADIUS*NODE_RADIUS)){
            drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
            return node;
        }
    }
    
    cout << "Invalid click. Please try again." << endl;
    return getNodeFromClick(start, graph);
}

Path findShortestPath(Node *start, Node *finish) {
    Path path;
    PriorityQueue< Path > queue;
    Map<string,double> fixed;
    while (start != finish) {
        if (!fixed.containsKey(start->name)) {
            fixed.put(start->name, path.totalCost());
            foreach (Arc *arc in start->arcs) {
                if (!fixed.containsKey(arc->finish->name)) {
                    path.addArc(arc);
                    queue.enqueue(path, path.totalCost());
                    path.removeLast();
                } }
        }
        if (queue.isEmpty()) {
            path.clear();
            return path;
        }
        path = queue.dequeue();
        start = path.getArc(path.numArcs()-1)->finish;
    }
    return path;
}

void highlightPath(Path path){    
    for(int i = 0; i < path.numArcs(); i++){
        drawPathfinderNode(path.getArc(i)->finish->loc, HIGHLIGHT_COLOR, path.getArc(i)->finish->name);
        drawPathfinderArc(path.getArc(i)->start->loc, path.getArc(i)->finish->loc, HIGHLIGHT_COLOR);
    }
}

void dijkstraAction(PathfinderGraph& graph){
    drawMap(graph); //called inorder to unhighlight if left highlighted from previous path.
    Node* start = getNodeFromClick(true, graph);
    Node* finish = getNodeFromClick(false, graph);
    Path path = findShortestPath(start, finish);
    highlightPath(path);
}

void kruskalAction(PathfinderGraph& graph){
    drawMap(graph);
    //create a map of nodes to the set of nodes that are connected to them.
    Map<Node*, Set<Node*> > connectedNodes;
    foreach(Node* node in graph.getNodes()){
        Set<Node*> initSet;
        initSet.add(node);
        connectedNodes[node] = initSet;
    }
    
    PriorityQueue<Arc*> queue;
    foreach(Arc* arc in graph.getArcs()){
        queue.enqueue(arc, arc->cost);
    }
    
    Set<Arc*> spanningArcs;
    while(true){
        Arc* arc = queue.dequeue();
        Node* start = arc->start;
        Node* finish = arc->finish;
        //Check if nodes already connected.
        if(!connectedNodes[start].contains(finish) && !connectedNodes[finish].contains(start)){
            spanningArcs += arc;
            //Here we merge the sets of connected nodes for both nodes.
            foreach(Node* node in connectedNodes[finish]){
                connectedNodes[start] += connectedNodes[node];
                connectedNodes[node] += connectedNodes[start];
            }
            foreach(Node* node in connectedNodes[start]){
                connectedNodes[finish] += connectedNodes[node];
                connectedNodes[node] += connectedNodes[finish];
            }
            //break if we have merged all the nodes.
            if(connectedNodes[start].size() == graph.numberNodes()) break;
        }
    }
    
    foreach(Arc* arc in spanningArcs){
        drawPathfinderArc(arc->start->loc, arc->finish->loc, HIGHLIGHT_COLOR);
    }
    
    foreach(Node* node in graph.getNodes()){
        drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
    }
}

/* Main program */

int main() {
    initPathfinderGraphics();
    
    PathfinderGraph graph;
    ifstream mapData;
    promptUserForFile(mapData); 
    readFile(graph, mapData); //A function that reads the map file and fills the graph from the data.

    drawMap(graph); //initially plot out map.
    
    //add buttons
    addButton("Map", mapAction, graph);
    addButton("Dijkstra", dijkstraAction, graph);
    addButton("Kruskal", kruskalAction, graph);
    addButton("Quit", quitAction);
    pathfinderEventLoop();
    
    
    return 0;
}

/* Sample callback function */

void quitAction() {
   exit(0);
}
