#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include <cassert>
#include <algorithm>
#include <vector>
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

	//cout << "Enter no of vertices and edges: ";
	int m;		// no of edges
	is >> this->nvertices >> m;

	//cout << "Enter edges:" << endl;
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
	for(int i=0;i<=MAXV;++i) {
		visited[i] = false;
		processed[i] = false;
		parent[i] = -1;
		entryTime[i] = -1;
		exitTime[i] = -1;
	}
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

bool graph::isTwoColorGraph() {
	COLOR colors[nvertices+1];
	for(int i=0;i<=nvertices;++i)
		colors[i] = UNCOLORED;

	bool isBipartite = true;
	initialize_search();
	for(int i=1;i<nvertices && isBipartite;++i) {
		if(!visited[i])
			isBipartite = bfsTwoColor(colors, i);
	}
	return isBipartite;
}

bool graph::bfsTwoColor(COLOR colors[], int start) {
	deque<int> q;
	q.push_back(start);

	COLOR parentColor = UNCOLORED;
	colorMe(colors, start, parentColor);
	visited[start] = true;

	while(!q.empty()) {
		int front = q.front();
		q.pop_front();
		parentColor = colors[front];

		edgenode *v = edges[front];
		while(v != NULL) {
			if(!visited[v->y]) {
				q.push_back(v->y);
				visited[v->y] = true;
				colorMe(colors,v->y,parentColor);
			}
			else if(directed || !processed[v->y]) {
				if(colors[v->y] == parentColor)
					return false;
			}
			v = v->next;
		}
		processed[front] = true;
	}
	return true;
}

void graph::colorMe(COLOR colors[], int i, COLOR parentColor) {
	if(parentColor == UNCOLORED || parentColor == BLACK)
		colors[i] = WHITE;
	else
		colors[i] = BLACK;
}

void graph::dfs_traversal(int start) {
	initialize_search();
	dfs_travel_internal(start);
}

void graph::dfs_travel_internal(int start) {
	visited[start] = true;
	cout << "Processing vertex " << start << endl;
	edgenode *edge = edges[start];

	while(edge != NULL) {
		if(visited[edge->y] == false) {
			cout << "Found edge (" << start << ", " << edge->y << ")" << endl;
			parent[edge->y] = start;
			dfs_travel_internal(edge->y);
		}
		else if(directed || (!processed[edge->y] && edge->y != parent[start]))
			cout << "Found edge (" << start << ", " << edge->y << ")" << endl;
	 	edge = edge->next;
	}
	processed[start] = true;
}

namespace {
	struct Pair {
		int index;
		int value;

		Pair(int i, int v): index(i), value(v) {}
	};

	int compareValue(Pair p1, Pair p2) {
		return p1.value > p2.value;
	}
}

// only for directed graphs
void::graph::topologicalSort() {
	time = 0;
	initialize_search();
	assert(directed == true);

	for(int i=1;i<=nvertices;++i) {
		if(!visited[i])
			dfs_topological(i);
	}

	vector<Pair> pairs;
	for(int i=1;i<=nvertices;++i) {
		Pair pair(i, exitTime[i]);
		pairs.push_back(pair);
	}

	std::sort(pairs.begin(), pairs.end(), compareValue);

	cout << "Topological Sort order:\n";
	for(int i=0;i<nvertices;++i) {
		cout << pairs[i].index << " ";
	}
	cout << endl;

}

void graph::dfs_topological(int x) {
	visited[x] = true;
	entryTime[x] = ++time;

	edgenode* edge = edges[x];
	while(edge != NULL) {
		int y = edge->y;
		if(visited[y] == false) {
			dfs_topological(y);
		}
		edge = edge->next;
	}
	exitTime[x] = ++time;
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

void test_graphs::twoColor() {
	graph g(false);
	cout << "Creating undirected graph" << endl;
	ifstream ifs("resources/graphs_disjoint.txt");
	g.read_graph(ifs);
	assert(g.isTwoColorGraph() == true);

	graph g2(false);
	cout << "Creating undirected graph" << endl;
	ifstream ifs2("resources/graph_bfs.txt");
	g2.read_graph(ifs2);
	assert(g2.isTwoColorGraph() == false);

	graph g3(true);
	cout << "Creating directed graph" << endl;
	ifstream ifs3("resources/graph_bipartite.txt");
	g3.read_graph(ifs3);
	assert(g3.isTwoColorGraph() == true);

}

void test_graphs::dfs_traversal() {
//	graph g(false);
//	cout << "Creating undirected graph" << endl;
//	ifstream ifs("resources/graphs_disjoint.txt");
//	g.read_graph(ifs);
//	g.dfs_traversal(1);

	graph g2(false);
	cout << "Creating undirected graph" << endl;
	ifstream ifs2("resources/graph_bfs.txt");
	g2.read_graph(ifs2);
	g2.dfs_traversal(1);
	// print parent array
	for(int i=1;i<=g2.nvertices;++i) {
		cout << g2.getParent(i) << " ";
	}
	cout << endl;

	/*graph g3(true);
	cout << "Creating directed graph" << endl;
	ifstream ifs3("resources/graph_bipartite.txt");
	g3.read_graph(ifs3);
	g3.dfs_traversal(1);*/
}

void test_graphs::testTopological() {
//	graph g1(true);
//	ifstream ifs1("resources/graph_topo.txt");
//	g1.read_graph(ifs1);
//	g1.topologicalSort();

	graph g2(true);
	ifstream ifs2("resources/graph_topo2.txt");
	g2.read_graph(ifs2);
	g2.topologicalSort();

}


