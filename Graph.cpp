#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
using namespace std;


graph::graph(bool directed) {
	this->nvertices = 0;
	this->nedges = 0;
	this->directed = directed;

	for (int i = 1; i <= MAXV; ++i)		// starts with 1. I guess 0 is just ignored?
		this->degree[i] = 0;
	for (int i = 1; i <= MAXV; ++i)
		this->edges[i] = NULL;

}

void graph::read_graph(bool directed, istream& is) {
	read_graph(this->directed, is);
}

void graph::read_graph(istream& is) {

	cout << "Enter no of vertices and edges: ";
	int m;		// no of edges
	is >> this->nvertices >> m;

	cout << "Enter edges:" << endl;
	for (int i = 1; i <= m; ++i) {
		int x, y;	// edge from vertex x to y
		is >> x >> y;
		insert_edge(x, y, directed);
	}
}

void graph::insert_edge(int x, int y, bool directed) {
	edgenode *p;
	p = new edgenode;
	p->weight = 0;
	p->y = y;

	//insert p at the head of linked list for vertex x's edges
	p->next = this->edges[x];
	this->edges[x] = p;
	this->degree[x]++;

	if (!directed)
		insert_edge(y, x, true);
	else
		++(this->nedges);
}

void graph::print_graph() {
	for (int i = 1; i <= this->nvertices; ++i) {
		edgenode *node = this->edges[i];
		while(node != NULL) {
			cout << "(" << i << ", " << node->y << ")  ";
			node = node->next;
		}
		cout << endl;
	}
}

void graph::initialize_search() {
	// initialize visited and processed array
	for(int i=0;i<=MAXV;++i)
		visited[i] = false;
	for(int i=0;i<=MAXV;++i)
		processed[i] = false;
	for(int i=0;i<=MAXV;++i)
		parent[i] = -1;
}

void graph::bfs_traversal(int start) {

	std::deque<int> queue;
	queue.push_back(start);
	visited[start] = true;
	cout << "Begin traversal:" << endl;
	while(!queue.empty()) {

		int front = queue[0];
		queue.pop_front();

		cout << "At vertex " << front << endl;

		// for all outgoing edges from front
		edgenode *edge = this->edges[front];
		while(edge != NULL) {
			if(!visited[edge->y]) {
				queue.push_back(edge->y);
				visited[edge->y] = true;
			}
			if(this->directed || !processed[edge->y])
				cout << "(" << front << ", " << edge->y << ")  " << endl;
			edge = edge->next;
		}
		processed[front] = true;
	}
	cout << "End traversal" << endl;
}

int graph::connected_componenets() {
	if(directed) {
		cerr << "Finding connected components makes sense only for undirected graphs" << endl;
		return 0;
	}
	int count = 0;
	initialize_search();
	for(int i=1;i<=nvertices;++i) {
		if(processed[i] == false) {
			++count;
			bfs_traversal(i);
		}
	}
	return count;
}

// tests
void test_graphs::graphCreation() {

	// Directed Graph
	graph g(false);
	cout << "Creating directed graph" << endl;
	ifstream ifs("resources/graph1.txt");
	g.read_graph(ifs);
	g.print_graph();

	// Undirected graph
	graph g2(false);
	cout << "Now creating an undirected graph" << endl;
	ifstream ifs2("resources/graph2.txt");
	g2.read_graph(ifs2);
	g2.print_graph();
}

void test_graphs::bfs_traversal() {
	graph g(false);
	cout << "Creating undirected graph" << endl;
	ifstream ifs("resources/graph_bfs.txt");
	g.read_graph(ifs);
	g.bfs_traversal(1);
}

void test_graphs::connected_componenets() {
	graph g(false);
	cout << "Creating undirected graph" << endl;
	ifstream ifs("resources/graphs_disjoint.txt");
	g.read_graph(ifs);
	cout << "No of connected components: " << g.connected_componenets() << endl;
}

