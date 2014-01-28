#include <iostream>
#include <list>
#include <fstream>
#include <stdlib.h>
#include "fibonacciheap.h"
#include <limits.h>
#include <time.h>

using namespace std;
int stotalCost, ftotalCost;
/*
 * neighbor is a data structure which stores destination vertex and cost of an edge in graph
 * */

class neighbor {
public:
	int destVertex;
	int cost;

	neighbor(int d, int c);

};

/*
 * neighbor class is a data structure which contains destination vertex and cost of edges.
 *
 * */

neighbor::neighbor(int d, int c) {

	this->destVertex = d;
	this->cost = c;

}

/*
 * graph class
 * variable name description:
 * 	vertices: array of list of neighbor data structure. In this array index is source of an edge
 * 	and neighbor contains the destination vertices and costs of the edges
 * 	n: number of vertices.
 *
 * */

class graph {
public:
	int n;
	list<neighbor> * vertices;
	int totalMinCost;

	graph(int n);
	void addEdge(int source, neighbor node);
	int findMinCostVertex(int costs[], bool non_mst[]);
	void simpleSchemePrimMst();
	void printMst(int mst[]);
	void FibHeapPrimMst();
	bool isGraphConnected(int v);
	void DFS(int v, bool visited[]);
	void print();

};
/*
 * graph class constructor
 * */

graph::graph(int n) {
	this->n = n;
	totalMinCost = 0;
	vertices = new list<neighbor> [n];

}
/*
 * Function to add edge to a graph
 *
 * */

void graph::addEdge(int source, neighbor node) {

	vertices[source].push_back(node);

}

/*
 * This method is used to find the minimum cost in the array based prim's algorithm
 * input:
 * 	costs[]: array of costs from which min is extracted
 * 	non_mst[]:array to keep track of the vertices covered along the path
 * */

int graph::findMinCostVertex(int costs[], bool non_mst[]) {

	int minCost = INT_MAX, minVertex;

	for (int i = 0; i < n; i++) {
		if (non_mst[i] == false && costs[i] <= minCost) {
			minCost = costs[i];
			minVertex = i;
		}

	}
	return minVertex;

}

/*
 * Implementation of array based Prim's algorithm
 *
 *
 * */

void graph::simpleSchemePrimMst() {
	bool non_mst[n];
	int mst[n];
	int costs[n];

	for (int i = 0; i < n; i++) {
		costs[i] = INT_MAX;
		non_mst[i] = false;
	}

	costs[0] = 0;
	mst[0] = -1;
	int simMinCost = 0;

	for (int i = 0; i < n; i++) {

		int minVertex = findMinCostVertex(costs, non_mst);
		non_mst[minVertex] = true;
		simMinCost += costs[minVertex];
		list<neighbor>::iterator it;
		for (it = vertices[minVertex].begin(); it != vertices[minVertex].end();
				it++) {
			if (non_mst[(*it).destVertex] == false
					&& (*it).cost < costs[(*it).destVertex]) {
				mst[(*it).destVertex] = minVertex;
				costs[(*it).destVertex] = (*it).cost;

			}

		}

	}
	stotalCost = simMinCost;
	cout<< simMinCost<<endl;
	printMst(mst);

}

/*
 * This function is used to print the final output edges selected by the prim's algorithm
 * input:
 * 	mst[]: final array which contains edges.Array index is the source and array value is destination.
 * */

void graph::printMst(int mst[]) {

	for (int i = 1; i < n; i++) {
		cout << mst[i]<<" "<< i;
		cout << endl;
	}

}

/*
 * Implementation of Fibonacci heap based Prim's algorithm
 *
 *
 * */

void graph::FibHeapPrimMst() {
	bool non_mst[n];
	int mst[n];
	int costs[n];

	for (int i = 0; i < n; i++) {
		costs[i] = INT_MAX;
		non_mst[i] = false;
	}

	fibonacciheap* heap = new fibonacciheap;

	costs[0] = 0;
	heap->insertNode(0, 0);
	mst[0] = -1;
	int fibMinCost = 0;
	int minVertex;

	for (int i = 0; i < n; i++) {

		int tmp = heap->removeMin();
		if (tmp == -1)
			break;
		while (non_mst[tmp]) {
			tmp = heap->removeMin();
			if (tmp == -1)
				break;
		}
		fibMinCost += costs[tmp];
		non_mst[tmp] = true;

		list<neighbor>::iterator it;
		for (it = vertices[tmp].begin(); it != vertices[tmp].end(); it++) {
			if (non_mst[(*it).destVertex] == false
					&& (*it).cost < costs[(*it).destVertex]) {
				mst[(*it).destVertex] = tmp;
				costs[(*it).destVertex] = (*it).cost;

				heap->insertNode((*it).destVertex, (*it).cost);

			}

		}

	}
	ftotalCost = fibMinCost;
	cout<< fibMinCost<<endl;
	printMst(mst);

}

/*
 * This function creates the graph based on the graph given in the input file
 * input:
 * 	filename: name of the file which contains graph
 * output:
 * 	graph
 * */
graph createGraphFromFile(char* filename) {

	ifstream inputFile(filename);
	int n;
	int m;

	if (inputFile.is_open()) {

		inputFile >> n;
		graph g(n);
		inputFile >> m;
		for (int i = 0; i < m; i++) {
			int source;
			int d, c;
			inputFile >> source;
			inputFile >> d;
			inputFile >> c;
			neighbor n1(d, c);
			neighbor n2(source, c);
			g.addEdge(source, n1);
			g.addEdge(d, n2);

		}
		inputFile.close();

		return g;
	}

	else{
		cout << "no input file specified in the command line arguments.Exiting the Program..."<<endl;
		exit(1);
	}


}
/*
 *
 * This function creates the graph randomly for the number of vertices and density provided
 * input:
 * 	n: number of vertices
 * 	d: density of the graph
 *
 * 	output: Graph
 *
 */


graph createGraphRandomly(int n, int d) {

	graph g(n);
	int edgeCount = ((((n * (n - 1)) / 2) * d) / 100);
	int num = 0;
	while (num != edgeCount) {
		int s = rand() % n;
		int d = rand() % n;
		bool edgeFound = false;
		int ecost = (rand() % 1000) + 1;

		list<neighbor>::iterator it;
		if (s == d)
			continue;
		for (it = g.vertices[s].begin(); it != g.vertices[s].end(); it++) {
			if ((*it).destVertex == d) {
				edgeFound = true;
				break;
			}
		}
		for (it = g.vertices[d].begin();
				(!edgeFound) && it != g.vertices[d].end(); it++) {
			if ((*it).destVertex == d) {
				edgeFound = true;
				break;
			}
		}
		if (!edgeFound) {

			neighbor n1(d, ecost);
			neighbor n2(s, ecost);
			g.addEdge(s, n1);
			g.addEdge(d, n2);
			num++;

		}



	}

	return g;

}

/*
 * Depth first search on the graph.This function performs a DFS by marking the nodes covered in the array visited
 * input:
 * 	v: vertex
 * 	visited: array which is used to mark visited vertices
 *
 * */

void graph::DFS(int v, bool visited[]) {
	visited[v] = true;

	list<neighbor>::iterator i;
	for (i = vertices[v].begin(); i != vertices[v].end(); ++i)
		if (!visited[(*i).destVertex])
			DFS((*i).destVertex, visited);
}

/*
 *This function uses DFS to check if the graph is connected or not
 *
 *
 * */
bool graph::isGraphConnected(int v) {

	bool *visited = new bool[n];
	int final = 0;
	for (int i = 0; i < n; i++)
		visited[i] = false;


	DFS(v, visited);

	for (int i = 0; i < n; i++) {
		if (visited[i])
			final++;

	}
	if (final == n)
		return true;
	else
		return false;
}

/*
 *
 * Function to print graph
 *
 *
 * */
void graph::print() {

	for (int v = 0; v < n; v++) {
		cout << endl << " Vertex " << v << " ";
		list<neighbor>::iterator i;
		for (i = vertices[v].begin(); i != vertices[v].end(); ++i)
			cout << v << "---" << (*i).destVertex << "(" << (*i).cost << ")";

	}

}

/*
 *
 * Main Function. This function takes the command line arguments and apply prim's algorithm on the graph
 * sample input:
 * File based input:
 * 	-s input.txt (-s apply's array based prim's algorithm to find minimum cost spanning tree on the graph given in the input.txt.
 * 	If -f is provided as input fibonacci heap based prim's algorithm is applies )
 * Random mode:
 * 	-r n d (-r applies both array and fibonacci heap based prim's algorithm to find minimum cost spanning tree on the graph generated)
 *
 *
 * */
int main(int argcount, char *args[]) {

	srand(time(0));
	if(argcount<2) {

				cout<<"Please rerun the program with command line arguments in any of the formats shown below \n -r n d \n -s input.txt \n -f input.txt"<<endl;

	} else if (string(args[1]) == "-r") {
		if(args[2]==NULL){
			cout<<"Number of vertices is not provided.Exiting the program..."<<endl;
			exit(1);
		}
		int n = atoi(args[2]);
		if(args[3]==NULL){
					cout<<"density is not provided.Exiting the program..."<<endl;
					exit(1);
				}
		int d = atoi(args[3]);

		graph g = createGraphRandomly(n, d);

		while (!g.isGraphConnected(0)) {

			g = createGraphRandomly(n, d);
		}

		clock_t Start, Time, sTime, fTime;
		Start = clock();
		g.simpleSchemePrimMst();
		Time = clock() - Start;
		sTime = Time;
		//cout<<" Time Taken for Simple Scheme "<<sTime<<" microseconds"<<endl;

		Start = clock();
		g.FibHeapPrimMst();
		Time = clock() - Start;
		fTime = Time;
		//cout<<" Time Taken for f-heap scheme "<<fTime<<" microseconds"<<endl;

	} else if (string(args[1]) == "-s") {

		graph g = createGraphFromFile(args[2]);
		g.simpleSchemePrimMst();

	} else if (string(args[1]) == "-f") {
		graph g = createGraphFromFile(args[2]);
		g.FibHeapPrimMst();

	}

}
