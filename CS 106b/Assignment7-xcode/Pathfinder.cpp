/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: Ryan Foley
 * Section: Brett Wines
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// Note: I believe I added all of the extensions correctly - although I did not do the "Let the user trigger Dijkstra’s algorithm by clicking on two nodes" extension.

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
#include <math.h> //for calculating square root and exponents
using namespace std;

/* Function prototypes */

void quitAction();

/* This function prompts the user for the name of the file that contains the map data - e.g. usa.txt. */
string promptUserForFilename() {
    while (true) {
        //get filename from user and open the file.
        cout << "Please enter filename containing map data: " << endl;
        string filename;
        getline(cin, filename); 
        
        ifstream mapData;
        mapData.open(filename.c_str()); 
        //send an error if cannot open the file and try again.
        if (!mapData.fail()){
            mapData.close(); //close the associated file so it can be openned later.
            return filename;
        }
        mapData.clear();
        cout << "Unable to open that file.  Try again." << endl;
    } 
}

/* A function that given the map data file reads all of the nodes from the file and puts them into the graph structure. */
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
        //get the x and y coordinates, the next two numbers. Scanner makes them type string, so must convert to int.
        string next = scanner.nextToken();
        int x = stringToInteger(next);
        next = scanner.nextToken();
        int y = stringToInteger(next);
        
        graph.addNode(city, x, y);
    }
}

/* A function that reads the map data file and imports all of the arcs into the graph structure. */
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
        double cost = stringToReal(next);

        graph.addArc(start, finish, cost);
        graph.addArc(finish, start, cost);
    }
}

/* A function that fills the set of Arcs in each Node with the arcs that have that node as there start. */
void fillArcsInNodes(PathfinderGraph& graph){
    foreach(Arc* arc in graph.getArcs()){
        foreach(Node* node in graph.getNodes()){
            if(arc->start == node) node->arcs += arc;
        }
    }
}

/* Given the name of the map data file, this function - along with the use of a few others - extracts the data and creates the corresponding graph structure. */
void getGraphFromFile(PathfinderGraph& graph, string filename){ 
    ifstream mapData;
    mapData.open(filename.c_str()); 
    
    // Get the first line which corresponds to the name of the image file for the map and draw the map image.
    string imageFileName;
    getline(mapData, imageFileName);
    drawPathfinderMap(imageFileName);
    
    // Get next line which should be the word NODES
    string line;
    getline(mapData, line);
    if(line != "NODES") error("Wrong file format"); //a check to make sure that file reading is going correctly.
    
    // Get all of the Nodes and Arcs from the file and put them into the graph.
    getNodes(graph, mapData);
    getArcs(graph, mapData);
    fillArcsInNodes(graph); // Filling the set of Arcs in each Node that are the Arcs from that Node.
    
    mapData.close();
}

/* This function draws the graph of nodes and arcs on to the map. */
void drawMap(PathfinderGraph& graph){
    // Drawing the nodes:
    foreach(Node* node in graph.getNodes())
        drawPathfinderNode(node->loc, NODE_COLOR, node->name);
    
    // Drawing the arcs:
    foreach(Arc* arc in graph.getArcs())
        drawPathfinderArc(arc->start->loc, arc->finish->loc, ARC_COLOR);
}

/* The following is the function corresponding to the "Map" button. - Allows user to change the map. */
void mapAction(string& filename){
    filename = promptUserForFilename(); // Get new filename for map.
    repaintPathfinderDisplay();
    
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    drawMap(graph);
}

/* A function that works with Dijkstra to get the start and finish nodes from the user's clicks on the map. Note: the bool, start, merely indicates whether the node being assigned is the start node - TRUE - or finish node - FALSE. */
Node* getNodeFromClick(bool start, PathfinderGraph& graph){
    //Prompt user to click appropriate node:
    if(start) cout << "Click on starting location... " << endl;
    else cout << "Click on finishing location... " << endl;
    
    // Assign the mouse click from the user to GPoint and get its coordinates. 
    GPoint pt = getMouseClick();
    double x = pt.getX();
    double y = pt.getY();
    
    // Find node clicked on, highlight it, and return it.
    Set<Node*> nodes = graph.getNodes();
    foreach(Node* node in nodes){
        double nodeX = node->loc.getX();
        double nodeY = node->loc.getY();
        
        // Made node radius slightly larger - multiplying the euclidean distance by sqrt of 2 - to make a little easier to click.
        if(pow(x - nodeX, 2) + pow(y - nodeY, 2) <= 2*pow(NODE_RADIUS, 2)){
            drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
            return node;
        }
    }
    
    // No node was clicked on, so return message and repeat function.
    cout << "Invalid click. Please try again." << endl;
    return getNodeFromClick(start, graph);
}

/* This function works with the Dijkstra action to find the shortest path from the start node to the finish. */
Path findShortestPath(Node *start, Node *finish, int length, int& count) {
    Path path;
    PriorityQueue< Path > queue;
    Map<string,double> fixed;
    while (start != finish and path.numArcs() <= length) {
        if (!fixed.containsKey(start->name)) {
            fixed.put(start->name, path.totalCost());
            foreach (Arc *arc in start->arcs) {
                if (!fixed.containsKey(arc->finish->name)) {
                    path.addArc(arc);
                    queue.enqueue(path, path.totalCost());
                    path.removeLast();
                } 
            }
        }
        if (queue.isEmpty()) {
            path.clear();
            return path;
        }
        path = queue.dequeue();
        start = path.getArc(path.numArcs()-1)->finish;
        count++;
    }
    // Check that last node is finish node. If it does not then return NULL.
    Arc* lastArc = path.getArc(path.numArcs()-1);
    if(lastArc->finish != finish){
        path.clear();
        return path;
    }
    
    //Otherwise, return the path found.
    return path;
}

/* A function that highlights the path and dims the remainding graph given the path from the Dijkstra action and the filename for the map. */
void drawDijkstra(Path& path, string filename){
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    
    // Color all of the graph in dim color.
    foreach(Arc* arc in graph.getArcs()){
        drawPathfinderArc(arc->start->loc, arc->finish->loc, DIM_COLOR);
    }
    foreach(Node* node in graph.getNodes()){
        drawPathfinderNode(node->loc, DIM_COLOR, node->name);
    }
    // Highlight the path.
    for(int i = 0; i < path.numArcs(); i++){
        drawPathfinderArc(path.getArc(i)->start->loc, path.getArc(i)->finish->loc, HIGHLIGHT_COLOR);
        drawPathfinderNode(path.getArc(i)->finish->loc, HIGHLIGHT_COLOR, path.getArc(i)->finish->name);
    }
}

/* The function called when the dijkstra button is clicked. It finds the shortest path between two nodes selected by the user. */
void dijkstraAction(string& filename){
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    drawMap(graph);
    
    //Get start and finish nodes for the path from the user.
    Node* start = getNodeFromClick(true, graph);
    Node* finish = getNodeFromClick(false, graph);
    
    //Get the path length from the user:
    int length = getInteger("Please enter the maximum number of segments you would like in your route: ");
    
    //Calculate shortest path and highlight it. Note that count is a integer keeping track of the number of paths considered by the Shortest Path Algorithm - it is used by the A* function.
    int count = 0;
    Path path = findShortestPath(start, finish, length, count);
    
    //If path is NULL then no path of desired length was found, so report that and do not display a path.
    if(path.numArcs() == 0){
        cout << "No path of desired length was found" << endl;
        return;
    }
    drawDijkstra(path, filename);
    
    //Print out the shortest path:
    cout << "The shortest path is: " << path.toString() << endl;
}

/* This is a function that prints out the list of edges in order of cost. */
void printArcs(Set<Arc*> spanningArcs){
    PriorityQueue<Arc*> queue;
    foreach(Arc* arc in spanningArcs){
        queue.enqueue(arc, arc->cost);
    }
    cout << "Edges used in order of cost: " << endl;
    
    while(!queue.isEmpty()){
        Arc* arc = queue.dequeue();
        if(spanningArcs.contains(arc))
            cout << arc->cost << ": " << arc->start->name << " - " << arc->finish->name << endl;
    }
}
    
/* A function that highlights the spanning tree found from the Kruskal function. */
void drawKruskal(Set<Arc*> spanningArcs, PathfinderGraph& graph){
    foreach(Arc* arc in spanningArcs){
        drawPathfinderArc(arc->start->loc, arc->finish->loc, HIGHLIGHT_COLOR);
    }
    
    foreach(Node* node in graph.getNodes()){
        drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
    }
}

/* The function for the Kruskal algorithm finding the minimum spanning tree for the map. */
void kruskalAction(string& filename){
    // Let user know that Kruskal is running.
    cout << "Finding minimum spanning tree using Kruskal..." << endl;
    
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);

    // Create a map of nodes to the set of nodes that are connected to them.
    Map<Node*, Set<Node*> > connectedNodes;
    foreach(Node* node in graph.getNodes()){
        Set<Node*> initSet;
        initSet.add(node);
        connectedNodes[node] = initSet;
    }
    
    // Enqueue all arcs into the graph into a Priority Queue ordered by lowest cost/length to highest.
    PriorityQueue<Arc*> queue;
    foreach(Arc* arc in graph.getArcs()){
        queue.enqueue(arc, arc->cost);
    }
    
    // Find the set of Arcs that span the map based on Kruskal's algorithm.
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
    
    drawKruskal(spanningArcs, graph);
    printArcs(spanningArcs); // this is function that replicates the output of the sample program by printing out the arcs used in the spanning tree.
}

/* This is a function that is a modification of the shortest path algorithm. It includes the heuristic approach of prioritzing paths also by their distance from the finish. */

Path findAStarPath(Node* start, Node* finish, int& count){
    Path path;
    PriorityQueue< Path > queue;
    Map<string,double> fixed;    
    while (start != finish) {
        if (!fixed.containsKey(start->name)) {
            fixed.put(start->name, path.totalCost());
            foreach (Arc *arc in start->arcs) {
                if (!fixed.containsKey(arc->finish->name)) {
                    path.addArc(arc);
                    
                    //Calculate the euclidean distance of the last node in each path from the finish node.
                    Node* node = arc->finish;
                    double nodeX = node->loc.getX();
                    double nodeY = node->loc.getY();
                    
                    double finishX = finish->loc.getX();
                    double finishY = finish->loc.getY();
                    
                    double distance = sqrt(pow(nodeX - finishX, 2) + pow(nodeY - finishY, 2));
                    
                    //Now penalizing of new path's priority by euclidean distance of the new arc's end node from the finish:
                    queue.enqueue(path, path.totalCost() + distance);
                    path.removeLast();
                } 
            }
        }
        if (queue.isEmpty()) {
            path.clear();
            return path;
        }
        path = queue.dequeue();
        start = path.getArc(path.numArcs()-1)->finish;
        count++;
    }
    // Check that last node is finish node. If it does not then return NULL.
    Arc* lastArc = path.getArc(path.numArcs()-1);
    if(lastArc->finish != finish){
        path.clear();
        return path;
    }
    
    //Otherwise, return the path found.
    return path;
}

/* A function that is an extension of the assignment. It uses a heuristic approach to finding the shortest path by adding in the euclidean distance of the paths last node from the finish node so as to prioritze paths by closeness to the finish. */

void AStarAction(string& filename){
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    drawMap(graph);
    
    //Get start and finish nodes for the path from the user.
    Node* start = getNodeFromClick(true, graph);
    Node* finish = getNodeFromClick(false, graph);
    
    //Calculate shortest path and highlight it.
    int length = 1000;
    int count = 0;
    Path dijkstraPath = findShortestPath(start, finish, length, count);
    cout << "The Dijkstra algorithm considered " << count << " paths in finding a solution." << endl;
    
    //Find the shortest path using the heuristic approach described.
    count = 0;
    Path aStarPath = findAStarPath(start, finish, count);
    
    drawDijkstra(aStarPath, filename);
    
    cout << "The A* algorithm considered " << count << " paths in finding a solution." << endl;
    
    //Print out the shortest path:
    cout << "The shortest path is: " << aStarPath.toString() << endl;
    cout << "It has length: " << aStarPath.totalCost() << endl;
}

/* A function finding the eccentricity of each node. */

Map<Node*, double> calculateEccentricities(Set<Node*> nodes){
    Map<Node*, double> eccentricity;
    
    Vector<Node*> nodesVec;
    foreach(Node* node in nodes){
        nodesVec += node;
    }
    
    for(int i = 0; i < nodesVec.size(); i++){
        eccentricity.put(nodesVec[i], 0);
        
        for(int q = 0; q < nodesVec.size(); q++){
            if(nodesVec[i]->name != nodesVec[q]->name){
                //count and length are merely dummy variables here.
                int count = 0;
                Path path = findAStarPath(nodesVec[i], nodesVec[q], count);
                if(eccentricity[nodesVec[i]] < path.totalCost()) 
                    eccentricity.put(nodesVec[i], path.totalCost());
                path.clear();
            }
        }
    }
    return eccentricity;
}

/* A function finding the smallest eccentricity. */

double findSmallestEccentricity(Map<Node*, double> eccentricities){
    double smallestEccentricity = -1;
    foreach(Node* node in eccentricities){
        if(smallestEccentricity == -1) 
            smallestEccentricity = eccentricities[node];
        else{
            if(smallestEccentricity > eccentricities[node])
                smallestEccentricity = eccentricities[node];
        }
    }
    return smallestEccentricity;
}


/* A function that finds the center(s) of a graph by calculating eccentricity. */

void findCenterAction(string& filename){
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    drawMap(graph);
    
    Map<Node*, double> eccentricities = calculateEccentricities(graph.getNodes());
    
    double smallestEccentricity = findSmallestEccentricity(eccentricities);
    
    //Print out all possible centers (those nodes that have the smallest eccentricity):
    
    cout << "Possible graph centers are: " << endl;
    foreach(Node* node in eccentricities){
        if(eccentricities[node] == smallestEccentricity){
            cout << node->name << endl;
            drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
        }
    }
}

/* A function that returns all of the neighbors of a node. */

Set<Node*> N(Node* node){
    Set<Node*> neighbors;
    foreach(Arc* arc in node->arcs){
        neighbors += arc->finish;
    }
    return neighbors;
}

/* A function that finds the intersection between two sets of nodes. */

Set<Node*> intersection(Set<Node*> nodes1, Set<Node*> nodes2){
    Set<Node*> intersectingNodes;
    foreach(Node* node in nodes1){
        if(nodes2.contains(node))
            intersectingNodes += node;
    }
    return intersectingNodes;
}

/* A function that carrys out the BronKerbosch Algo for finding the maximal clique. */

void BronKerbosch1(Set<Node*> R,Set<Node*> P,Set<Node*> X, Vector< Set<Node*> >& possibleCliques){
    if(P.isEmpty() && X.isEmpty()){
        possibleCliques += R;
        return;
    }
    foreach(Node* node in P){
        BronKerbosch1(R + node, intersection(P, N(node)), intersection(X, N(node)), possibleCliques);
        P -= node;
        X += node;
    }
}

void drawClique(Set<Node*> clique){
    foreach(Node* node in clique){
        drawPathfinderNode(node->loc, HIGHLIGHT_COLOR, node->name);
        foreach(Arc* arc in node->arcs){
            if(clique.contains(arc->finish))
                drawPathfinderArc(arc->start->loc, arc->finish->loc, HIGHLIGHT_COLOR);
        }
    }
}

/* Given a set of cliques this function finds the largest. */

Set<Node*> findMax( Vector< Set<Node*> > cliques){
    Set<Node*> maxClique;
    foreach(Set<Node*> clique in cliques){
        if(clique.size() >= maxClique.size())
            maxClique = clique;
    }
    return maxClique;
}

/* A function that finds the maximal clique for the graph. */

void maxCliqueAction(string& filename){
    PathfinderGraph graph;
    getGraphFromFile(graph, filename);
    drawMap(graph);
    
    Set<Node*> R;
    Set<Node*> P = graph.getNodes();
    Set<Node*> X;
    
    Vector< Set<Node*> > possibleCliques;
    BronKerbosch1(R,P,X, possibleCliques);
    
    Set<Node*> maxClique = findMax(possibleCliques);
    
    drawClique(maxClique);
    
    cout << "The following nodes form a maximal clique: " << endl; 
    foreach(Node* node in maxClique)
        cout << node->name << endl;
}

/* Main program */

int main() {
    cout<< "This masterful piece of work is a graph extravaganza!" << endl;
    cout<< "The main attractions include a lovely visual presentation" << endl;
    cout<< "of the graph along with an implementation of Dijkstra's " << endl;
    cout<< "shortest path algorithm and Kruskal's computation of" << endl;
    cout<< "a minimal spanning tree.  Enjoy!" << endl;
    
    initPathfinderGraphics();
    
    PathfinderGraph graph;
    string filename;
    
    filename = promptUserForFilename(); // Get the name of the data file from the user.
    getGraphFromFile(graph, filename); // A function that reads the map file and fills the graph from the data.
    drawMap(graph); // Initially plot out map.
    
    //add buttons
    addButton("Map", mapAction, filename);
    addButton("Dijkstra", dijkstraAction, filename);
    addButton("Kruskal", kruskalAction, filename);
    addButton("A*", AStarAction, filename);
    addButton("Find Center", findCenterAction, filename);
    addButton("Max Clique", maxCliqueAction, filename); 
    addButton("Quit", quitAction);
    pathfinderEventLoop();
    
    
    return 0;
}

/* Sample callback function */

void quitAction() {
   exit(0);
}
