/********************************************************
 * File: wiki-graph.cpp
 *
 * Code to play around with the Wikipedia graph.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "hashmap.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* Reads in the Wikipedia data. */
void readData(Vector<string>& articles, HashMap<string, int>& articleToIndex, HashMap<int, Vector<int> >& links) {
	/* Read article names into the first two parameters. */
	ifstream articlesFile("articles.txt");
	while (true) {
		string article;
		getline(articlesFile, article);
		
		if (articlesFile.fail()) break;
		
		articles += article;
		articleToIndex[article] = articles.size() - 1;
	}
	cout << "Read " << articles.size() << " articles." << endl;
	
	/* Read all of the links into the map. */
	ifstream linksFile("links.txt");
	int numLinks = 0;
	while (true) {
		int start;
		int end;
		
		linksFile >> start >> end;
		if (linksFile.fail()) break;
		
		links[start] += end;
		numLinks ++;
	}
	
	cout << "Read " << numLinks << " links." << endl;
}

/* Given the information we built up about the search from the 
 * start article to the end article, prints out the path we
 * found from the start to the end.
 */
void printPath(int start, int end, HashMap<int, int>& visited,
               Vector<string>& articles) {
               
	/* We have information relating each article to its parent, but we
	 * want the path in order from the start to the end.  Accordingly,
	 * we're going to push everything onto a stack so that as we walk
	 * the path in reverse order, we end up correcting the order here.
	 */
	Stack<int> path;
	while (true) {
		path.push(end);
		if (start == end) break;
		
		end = visited[end];
	}
	
	/* Print out the articles in order. */
	while (!path.isEmpty()) {
		cout << articles[path.pop()] << endl;
	}
}

/* Finds a path from the first node to the second. */
void findPathFrom(int from, int to, Vector<string>& articles,
                  HashMap<int, Vector<int> >& links) {
	/* This queue holds the current set of articles to work with.
	 * If we change it to a stack, we get a depth-first search.
	 */
	Queue<int> worklist;
	
	/* Information about what the parents of each article are in our
	 * breadth-first search tree.
	 */
	HashMap<int, int> visited;
	
	/* Enqueue the start article and mark that it's been visited.  The
	 * choice of making it its own parent is entirely arbitrary.
	 */
	worklist.enqueue(from);
	visited[from] = from;
	
	while (!worklist.isEmpty()) {
		/* Get the current node.  If it's the destination, we're done! */
		int curr = worklist.dequeue();
		if (curr == to) {
			printPath(from, to, visited, articles);
			return;
		}
		
		/* Consider each outgoing link.  If we haven't marked the article
		 * as visited, go follow the link to visit it.
		 */
		foreach (int link in links[curr]) {
			if (!visited.containsKey(link)) {
				worklist.enqueue(link);
				visited[link] = curr;
			}
		}
	}
}

int main() {
	/* Pull the Wikipedia data into the program. */
	Vector<string> articles;
	HashMap<string, int> articleToIndex;
	HashMap<int, Vector<int> > links;
	readData(articles, articleToIndex, links);
	
	/* Get two article names, then find a path between them. */
	while (true) {
		string first = getLine("Enter article title: ");
		if (!articleToIndex.containsKey(first)) {
			cout << "Sorry, I don't know that article." << endl;
			continue;
		}
		
		string second = getLine("Enter article title: ");
		if (!articleToIndex.containsKey(second)) {
			cout << "Sorry, I don't know that article." << endl;
			continue;
		}
		
		findPathFrom(articleToIndex[first], articleToIndex[second], articles, links);
	}
	
	return 0;
}
